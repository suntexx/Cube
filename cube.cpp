
#include <iostream>
//#include <stdio.h>
//#include <cstring>
//#include <cstdlib>
#include "global.h"
#include "cube.h"

Cube::Cube() {
  this->parts = new short[54];
  this->reset();
}

void Cube::reset() {
  for (short i = 54; i--;) this->parts[i] = (short) (i / 9);
}

short* Cube::clone(short* parts, short* res) {
  if (!parts) {
    if (!this->parts) return 0;
    parts = this->parts;
  }

  if (!res) res = new short[54];
  memcpy(res, parts, CUBE_SIZE);
  return res;
}

void Cube::removeClone(short*&parts) {
  if (!parts) return;
  delete[] parts;
  parts = 0l;
}

void Cube::setSquare(short id, short val) { this->parts[id] = val; }

short* Cube::getValues() { return this->clone(this->parts); }

short* Cube::getValues(short* destination) {
  if (!destination) return 0;//this->getValues();
  memcpy(destination, this->parts, CUBE_SIZE);
  return destination;
}

short* Cube::setValues(short* parts) {
  if (!parts) return 0;
  return this->clone(parts);
//  return this->parts;
}

void Cube::setValues(char* parts) {
  if (!parts) return;
  if (!this->parts) this->parts = new short[54];
  for (int i = 0; i < 54; i++) this->parts[i] = (short) (parts[i] - '0');
}

short Cube::mapX(short square, short x, short y) { return (short) ((square == 4) ? (9 * square - 3 * y - x + 8) : (9 * square + 3 * y + x)); }

void Cube::rotateX(short pos, bool dir) {
  short clone[54] = { 0 };
  this->getValues(clone);

  const short matrix[] = { 0, 4, 5, 2 };
  short t, n, x;

  for (n = 4; n--;)
    for (x = 3, t = (short) ((n + (!dir ? -1 : 1) + 4) % 4); x--;) this->setSquare(this->mapX(matrix[n], pos, x), clone[this->mapX(matrix[t], pos, x)]);

  if (pos != 1) this->rotateSide((short) (!pos ? 1 : 3), (bool) (pos ? dir : !dir));
}

void Cube::rotateXFull(bool dir) { for (int pos = 0; pos < 3; pos++) this->rotateX(pos, dir); }

short Cube::mapY(short square, short x, short y) { return (short) (9 * square + 3 * y + x); }

void Cube::rotateY(short pos, short dir) {
  short clone[54] = { 0 };
  this->getValues(clone);

  const short matrix[] = { 1, 2, 3, 4 };
  short t, n, x;

  for (n = 4; n--;)
    for (x = 3, t = (short) ((n + (!dir ? -1 : 1) + 4) % 4); x--;) this->setSquare(this->mapY(matrix[n], x, pos), clone[this->mapY(matrix[t], x, pos)]);

  if (pos != 1) this->rotateSide((short) (!pos ? 0 : 5), pos ? dir : !dir);
}

void Cube::rotateYFull(bool dir) { for (short pos = 0; pos < 3; pos++) this->rotateY(pos, dir); }

short Cube::mapZ(short square, short x, short y) {
  switch (square) {
    case 5:
      return (short) (9 * square + 3 * x - y + 2);
    case 0:// 3 * (2 - position) + z;
      return (short) (9 * square - 3 * x + y + 6);

    case 1:// (2 - position) + 3 * (2 - z);
      return (short) (9 * square - x - 3 * y + 8);
    case 3:
      return (short) (9 * square + x + 3 * y);

    default:
      return 0;
  }
}

void Cube::rotateZ(short pos, bool dir) {
  short clone[54] = { 0 };
  this->getValues(clone);

  const short matrix[] = { 0, 3, 5, 1 };
  short t, n, i;

  for (n = 4; n--;)
    for (i = 3, t = (short) ((n + (!dir ? -1 : 1) + 4) % 4); i--;) this->setSquare(this->mapZ(matrix[n], pos, i), clone[this->mapZ(matrix[t], pos, i)]);
  if (pos != 1) this->rotateSide((short) (!pos ? 2 : 4), !pos ? dir : !dir);
}

void Cube::rotateZFull(bool dir) { for (short pos = 0; pos < 3; pos++) this->rotateZ(pos, dir); }

void Cube::rotateSide(short sq, bool dir) {
  short clone[54] = { 0 };
  this->getValues(clone);

  const short matrix[9] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
  for (short n = 9; n--;) {
    if (n == 4) continue; // center - no move
    this->setSquare(9 * sq + n,
                    clone[9 * sq + matrix[!dir ? 8 - n : n]]);
  }

//  this->removeClone(clone);
}

bool Cube::isSolved(short* parts) {
  parts = !parts ? this->parts : parts;

  for (short sq = 6, i, clr; sq--;) {
    clr = parts[9 * sq];
    for (i = 9; --i;) {
      if (parts[9 * sq + i] != clr) return false;
    }
  }
  return true;
}

void Cube::rotate(MOVE move) { this->rotate(move.axis, move.pos, move.dir); }

void Cube::rotate(short i) { this->rotate(i >> 2, i & 2, i & 1); }

void Cube::rotate(short axis, short pos, bool dir) {
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

//short Cube::getColor(short id) { return (id < 0 || id > 53) ? (short) -1 : (this->parts[id]); }

//short Cube::getColorNum(short sq, short num) { return this->getColor((short) (sq * 9 + num)); }
//
//short Cube::getColorXY(short sq, short x, short y) { return this->getColor((short) (sq * 9 + y * 3 + x)); }
//
//short Cube::id2square(short id) { return (short) (id / 9); }
//
//short Cube::id2col(short id) { return (short) (id % 3); }
//
//short Cube::id2row(short id) { return (short) ((id % 9) / 3); }
//
//short Cube::getSquareXYID(short sq, short x, short y) { return (short) (sq * 9 + y * 3 + x); }

short Cube::getSquareNumID(short sq, short num) { return (short) (sq * 9 + num); }

void Cube::toString(char* str, short* parts) {
  parts = !parts ? this->parts : parts;
  for (int i = 0; i < 54; i++) {
//    if (i % 9 == 8) t++;
    str[i] = (char) (parts[i] + '0');
  }
}

void Cube::shuffle(int steps) {
  if (!steps || steps < 0) return;

  short tmp = (short) (rand() % 12),
      pos = (short) ((tmp & 2) ? 2 : 0),
      rand = tmp >> 2;
  bool dir = (tmp & 1) != 0;

//  if (typeof this.last != 'undefined') while (rand == this.last.rand) rand = (rand + this.rand(3)) % 3;

  if (rand == 2) this->rotateX(pos, dir);
  else if (rand == 1) this->rotateY(pos, dir);
  else this->rotateZ(pos, dir);

  if (steps > 0) this->shuffle(steps - 1);
};

char* Cube::move2str(MOVE move) {
  for (int i = 0; i < 24; i++) {
    if (this->moves_str[i].move == move) return (char*) this->moves_str[i].str;
  }

  return NULL;
};

char* Cube::moves2str(MOVES* moves, const char* separator) {
  size_t size = moves->count * (2 + strlen(separator)) + 1;
  char* res = new char[size];
  memset(res, 0, size);
  for (int i = 0; i < moves->count; i++) {
    strcat(res, this->move2str(moves->moves[i]));
    if (separator) strcat(res, separator);
  }

  return res;
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
void Cube::log(short s, Rest... rest) {
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