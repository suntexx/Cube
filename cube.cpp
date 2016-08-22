
#include <iostream>
#include "global.h"
#include "cube.h"

Cube::Cube() {
  this->parts = new unsigned char[54];
  this->reset();
}

Cube::Cube(unsigned char* parts) {
  this->parts = new unsigned char[54];
  this->reset();
  this->clone(parts);
}

void Cube::reset() {
  for (unsigned char i = 54; i--;) this->parts[i] = (unsigned char) (i / 9);
}

unsigned char* Cube::clone(unsigned char* parts, unsigned char* res) {
  if (!parts) {
    if (!this->parts) return 0;
    parts = this->parts;
  }

  if (!res) res = new unsigned char[54];
  memcpy(res, parts, CUBE_SIZE);
  return res;
}

void Cube::removeClone(unsigned char*&parts) {
  if (!parts) return;
  delete[] parts;
  parts = 0l;
}

void Cube::setSquare(unsigned char id, unsigned char val) { this->parts[id] = val; }

unsigned char* Cube::getValues() { return this->parts;/*this->clone(this->parts);*/ }

unsigned char* Cube::getValues(unsigned char* destination) {
  if (!destination) return 0;//this->getValues();
  memcpy(destination, this->parts, CUBE_SIZE);
  return destination;
}

unsigned char* Cube::setValues(unsigned char* parts) {
  if (!parts) return 0;
  return this->clone(parts);
//  return this->parts;
}

void Cube::setValues(char* parts) {
  if (!parts) return;
  if (!this->parts) this->parts = new unsigned char[54];
  for (int i = 0; i < 54; i++) this->parts[i] = (unsigned char) (parts[i] - '0');
}

unsigned char Cube::mapX(unsigned char square, unsigned char x, unsigned char y) { return (unsigned char) ((square == 4) ? (9 * square - 3 * y - x + 8) : (9 * square + 3 * y + x)); }

void Cube::rotateX(unsigned char pos, bool dir) {
  unsigned char clone[54] = { 0 };
  this->getValues(clone);

  const unsigned char matrix[] = { 0, 4, 5, 2 };
  unsigned char t, n, x;

  for (n = 4; n--;)
    for (x = 3, t = (unsigned char) ((n + (!dir ? -1 : 1) + 4) % 4); x--;) this->setSquare(this->mapX(matrix[n], pos, x), clone[this->mapX(matrix[t], pos, x)]);

  if (pos != 1) this->rotateSide((unsigned char) (!pos ? 1 : 3), (bool) (pos ? dir : !dir));
}

void Cube::rotateXFull(bool dir) { for (int pos = 0; pos < 3; pos++) this->rotateX(pos, dir); }

unsigned char Cube::mapY(unsigned char square, unsigned char x, unsigned char y) { return (unsigned char) (9 * square + 3 * y + x); }

void Cube::rotateY(unsigned char pos, unsigned char dir) {
  unsigned char clone[54] = { 0 };
  this->getValues(clone);

  const unsigned char matrix[] = { 1, 2, 3, 4 };
  unsigned char t, n, x;

  for (n = 4; n--;)
    for (x = 3, t = (unsigned char) ((n + (!dir ? -1 : 1) + 4) % 4); x--;) this->setSquare(this->mapY(matrix[n], x, pos), clone[this->mapY(matrix[t], x, pos)]);

  if (pos != 1) this->rotateSide((unsigned char) (!pos ? 0 : 5), pos ? dir : !dir);
}

void Cube::rotateYFull(bool dir) { for (unsigned char pos = 0; pos < 3; pos++) this->rotateY(pos, dir); }

unsigned char Cube::mapZ(unsigned char square, unsigned char x, unsigned char y) {
  switch (square) {
    case 5:
      return (unsigned char) (9 * square + 3 * x - y + 2);
    case 0:// 3 * (2 - position) + z;
      return (unsigned char) (9 * square - 3 * x + y + 6);

    case 1:// (2 - position) + 3 * (2 - z);
      return (unsigned char) (9 * square - x - 3 * y + 8);
    case 3:
      return (unsigned char) (9 * square + x + 3 * y);

    default:
      return 0;
  }
}

void Cube::rotateZ(unsigned char pos, bool dir) {
  unsigned char clone[54] = { 0 };
  this->getValues(clone);

  const unsigned char matrix[] = { 0, 3, 5, 1 };
  unsigned char t, n, i;

  for (n = 4; n--;)
    for (i = 3, t = (unsigned char) ((n + (!dir ? -1 : 1) + 4) % 4); i--;) this->setSquare(this->mapZ(matrix[n], pos, i), clone[this->mapZ(matrix[t], pos, i)]);
  if (pos != 1) this->rotateSide((unsigned char) (!pos ? 2 : 4), !pos ? dir : !dir);
}

void Cube::rotateZFull(bool dir) { for (unsigned char pos = 0; pos < 3; pos++) this->rotateZ(pos, dir); }

void Cube::rotateSide(unsigned char sq, bool dir) {
  unsigned char clone[54] = { 0 };
  this->getValues(clone);

  const unsigned char matrix[9] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
  for (unsigned char n = 9; n--;) {
    if (n == 4) continue; // center - no move
    this->setSquare(9 * sq + n,
                    clone[9 * sq + matrix[!dir ? 8 - n : n]]);
  }

//  this->removeClone(clone);
}

bool Cube::isSolved(unsigned char* parts) {
  parts = !parts ? this->parts : parts;

  for (unsigned char sq = 6, i, clr; sq--;) {
    clr = parts[9 * sq];
    for (i = 9; --i;) {
      if (parts[9 * sq + i] != clr) return false;
    }
  }
  return true;
}

void Cube::rotate(MOVE move) {
  switch (move.axis) {
    case 0: // X
      if (move.pos == 3) this->rotateXFull(move.dir);
      else this->rotateX(move.pos, move.dir);
      return;

    case 1: // Y
      if (move.pos == 3) this->rotateYFull(move.dir);
      else this->rotateY(move.pos, move.dir);
      return;

    case 2: // Z
      if (move.pos == 3) this->rotateZFull(move.dir);
      else this->rotateZ(move.pos, move.dir);
      return;

    default:
      return;
  }
}

void Cube::rotate(unsigned char i) { this->rotate(i >> 2, i & 2, i & 1); }

void Cube::rotate(unsigned char axis, unsigned char pos, bool dir) {
  switch (axis) {
    case 0: // X
      if (pos == 3) this->rotateXFull(dir);
      else this->rotateX(pos, dir);
      return;

    case 1: // Y
      if (pos == 3) this->rotateYFull(dir);
      else this->rotateY(pos, dir);
      return;

    case 2: // Z
      if (pos == 3) this->rotateZFull(dir);
      else this->rotateZ(pos, dir);
      return;

    default:
      return;
  }
}

//unsigned char Cube::getColor(unsigned char id) { return (id < 0 || id > 53) ? (unsigned char) -1 : (this->parts[id]); }

//unsigned char Cube::getColorNum(unsigned char sq, unsigned char num) { return this->getColor((unsigned char) (sq * 9 + num)); }
//
//unsigned char Cube::getColorXY(unsigned char sq, unsigned char x, unsigned char y) { return this->getColor((unsigned char) (sq * 9 + y * 3 + x)); }
//
//unsigned char Cube::id2square(unsigned char id) { return (unsigned char) (id / 9); }
//
//unsigned char Cube::id2col(unsigned char id) { return (unsigned char) (id % 3); }
//
//unsigned char Cube::id2row(unsigned char id) { return (unsigned char) ((id % 9) / 3); }
//
//unsigned char Cube::getSquareXYID(unsigned char sq, unsigned char x, unsigned char y) { return (unsigned char) (sq * 9 + y * 3 + x); }

unsigned char Cube::getSquareNumID(unsigned char sq, unsigned char num) { return (unsigned char) (sq * 9 + num); }

void Cube::toString(char* str, unsigned char* parts) {
  parts = !parts ? this->parts : parts;
  for (int i = 0; i < 54; i++) {
//    if (i % 9 == 8) t++;
    str[i] = (char) (parts[i] + '0');
  }
}

void Cube::shuffle(int steps) {
  if (!steps || steps < 0) return;

//  unsigned char tmp = (unsigned char) (rand() % 12),
//      pos = (unsigned char) ((tmp & 2) ? 2 : 0),
//      rand = tmp >> 2;
//  bool dir = (tmp & 1) != 0;

  MOVE move = int2move(rand() % 12);
  this->rotate(move);

//  if (typeof this.last != 'undefined') while (rand == this.last.rand) rand = (rand + this.rand(3)) % 3;

//  if (rand == 2) this->rotateX(pos, dir);
//  else if (rand == 1) this->rotateY(pos, dir);
//  else this->rotateZ(pos, dir);

  if (steps > 0) this->shuffle(steps - 1);
};


/*
template<typename T>
void Cube::log(T const &t) {
  std::cout << t << std::endl;
}

template<typename First, typename ... Rest>
void Cube::log(First const &first, Rest const &... rest) {
  std::cout << first;
  Cube::log(rest ...);
}
/ * /
void Cube::log() { std::cout << std::endl; }

template<typename ...Rest>
void Cube::log(int i, Rest... rest) {
  std::cout << i;
  Cube::log(rest...);
}

template<typename ...Rest>
void Cube::log(unsigned char s, Rest... rest) {
  std::cout << s;
  Cube::log(rest...);
}

template<typename ...Rest>
void Cube::log(float f, Rest... rest) {
  std::cout << f;
  Cube::log(rest...);
}

template<typename ...Rest>
void Cube::log(char const* c, Rest... rest) {
  std::cout << c;
  Cube::log(rest...);
}

template<typename T, typename ...Rest>
void Cube::log(T c, Rest... rest) {
  std::cout << c;
  Cube::log(rest...);
}

template<typename ...Rest>
void Cube::log(Rest... rest) {
//  std::cout << rest << std::endl;
//  Cube::log(rest...);
}
//*/