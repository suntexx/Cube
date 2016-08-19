
#ifndef CUBE_TESTER_H
#define CUBE_TESTER_H

#include "global.h"
#include "cube.h"

class Tester : private Cube {
private:
  short* storage;
  int steps = 0;
  short max = 0;
  short done = 0;

  MOVES* testStep(int step_num, short* parts, MOVE* last = 0, MOVE* last2 = 0);

  void store();

  void load();

  MOVES* addMoves(const MOVE move, MOVES* moves, bool begin = true);

  MOVES* simplifyMoves(MOVES*&moves, bool second = false);
//  char *prepareNumber(int x);

public:
  Tester(short* parts);

  int getSteps() { return this->steps; }

  MOVES* test(short steps);

  void move2str(MOVE move, char*);

  static void int2move(short i, MOVE &);

  static MOVE int2move(short i);
};

#include "tester.h"

#endif //CUBE_TESTER_H
