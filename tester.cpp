
#include <iostream>
//#include <stdio.h>
//#include <cstring>
//#include <cstdlib>
#include "global.h"
#include "tester.h"

Tester::Tester(short* parts) {
  this->parts = this->clone(parts);
  this->storage = 0l;
}

void Tester::store() {
  if (this->storage) this->removeClone(this->storage);
  this->clone(this->parts, this->storage);
}

void Tester::load() {
  if (!this->storage) return;
  this->parts = this->clone(this->storage);
  this->removeClone(this->storage);
  this->storage = 0l;
}

void Tester::int2move(short i, MOVE &m) {
  m.axis = (short) ((i >> 2));
  m.pos = (short) (i & 2);
  m.dir = (i & 1) != 0;
}

MOVE Tester::int2move(short i) {
  MOVE m;
  m.axis = (short) ((i >> 2));
  m.pos = (short) (i & 2);
  m.dir = (i & 1) != 0;
  return m;
}

void Tester::move2str(MOVE move, char* res) {
  sprintf(res, "[%i,%i,%i]", move.axis, move.pos, move.dir);
}

MOVES* Tester::addMoves(const MOVE move, MOVES* moves, bool begin) {
  if (!moves) {
    moves = new MOVES;
    memset(moves, 0, sizeof(MOVES));
  }

  MOVE* res = new MOVE[moves->count + 1];

  if (moves->count) memcpy(res + begin, moves->moves, sizeof(MOVE) * (moves->count));
  if (moves->moves) delete moves->moves;

  res[begin ? 0 : moves->count] = move;
  moves->moves = res;
  moves->count++;

  return moves;
}

MOVES* Tester::simplifyMoves(MOVES*&moves, bool second) {
  if (!moves) return 0;
  int a, b = 0, cnt = 0;
  MOVE last = { 0 };

  if (!second) {
    std::cout << "simplifying: ";

    char str[8] = { 0 };
    for (a = 0; a < moves->count; a++) {
      this->move2str(moves->moves[a], str);
      std::cout << str;
    }
    std::cout << std::endl;
  }

  MOVES* res = new MOVES;
  memset(res, 0, sizeof(MOVES));

  bool simplified = false;

  for (a = 0; a < moves->count; a++) {
    for (b = a + 1, cnt = 1; b < moves->count && moves->moves[a] == moves->moves[b]; b++, cnt++);
    if (cnt % 4 == 0) {
      simplified = true;
      a += cnt - 1;
      continue;
    }
    if (a < moves->count - 1 && moves->moves[a] == (!moves->moves[a + 1])) {//isMoveOpposite(moves->moves[a], moves->moves[a + 1])) {
      simplified = true;
      a++;
      continue;
    }
    last = (cnt % 4 == 3) ? (!moves->moves[a]) : moves->moves[a];
//    if (cnt % 4 == 3) last.dir = !last.dir;

    res = this->addMoves(last, res, false);

    if (cnt > 1 && cnt % 4 != 2) {
      a += cnt - 1;
      simplified = true;
    }
  }

  if (*moves != *res) {
    std::cout << "simplified: ";

    char str[8] = { 0 };
    for (a = 0; a < res->count; a++) {
      this->move2str(res->moves[a], str);
      std::cout << str;
    }
    std::cout << std::endl;
  }
  delete moves;

  return moves = ((simplified) ? this->simplifyMoves(res, true) : res);
}

MOVES* Tester::testStep(int step_num, short* parts, MOVE* last, MOVE* last2) {
  if (++step_num > this->max) return 0l;

  short i;
  short tmp[12][54] = { 0 };

  MOVES* result = 0;
  MOVES* moves = 0;
  MOVE move;
//  this->parts = tmp;
  for (i = 12; i--;) {
//    memcpy(tmp, parts, CUBE_SIZE);
    move = this->int2move(i);
    if (last && (move == !(*last) || (last2 && move == *last && move == *last2))) continue;
//    if (last && (move == !(*last))) continue;

    memcpy(this->parts = tmp[i], parts, CUBE_SIZE);
    this->steps++;
    this->rotate(i >> 2, i & 2, i & 1);

    if (this->isSolved(tmp[i])) {
      std::cout << "found: " << step_num << " | " << this->steps << std::endl;
      this->max = (short) (step_num - 1);//MIN(this->max, MAX(1, step_num - 1));

      this->parts = parts;
      return this->addMoves(this->int2move(i), moves);
    }
    /**** FASTEST (FIRST) SOLUTION **** /
    if ((moves = this->testStep(step_num, tmp[i])) != 0) {
      this->parts = parts;
      return this->addMoves(this->int2move(i), moves);
    }
    /*/
    if ((moves = this->testStep(step_num, tmp[i], &move, last)) != 0) {
      this->parts = parts;
      return this->addMoves(move, moves);
    }
    /**********************************/
  }

  /******* SHORTEST SOLUTION ******* /
  for (i = 12; i--;) {
    move = this->int2move(i);
    if (tmp[i] && (moves = this->testStep(step_num, tmp[i], &move, last)) != 0) {
      this->parts = parts;
      result = this->addMoves(move, moves);
//      if (step_num < 2) {
//        MOVES* simpl = new MOVES;
//        memcpy(simpl, moves, sizeof(MOVES));
//        this->simplifyMoves(simpl);
//        char* str = this->moves2str(simpl, " ");
//        std::cout << step_num << " " << str << std::endl;
//        delete[] str;
//        delete simpl;
//      }
    }
  }
  /**********************************/

  this->parts = parts;

  return result;
}

MOVES* Tester::test(short max = 5) {
  if (this->isSolved()) return 0;
  if (max < 0) max = 5;
  this->steps = 0;
  this->max = max;

  this->store();
  clock_t start = clock();

  MOVES* moves = this->testStep(0, this->parts);

  std::cout << "time: " << ((float) (clock() - start) / CLOCKS_PER_SEC) << " sec" << std::endl;

  this->load();
  return this->simplifyMoves(moves);
}
