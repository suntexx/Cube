
#ifndef CUBE_TESTER_H
#define CUBE_TESTER_H

#include "global.h"
#include "cube.h"

class Tester : private Cube {
private:
  unsigned char* storage;
  unsigned long steps = 0;
  unsigned char max = 0;
  unsigned char done = 0;

  const MOVE_STR moves_str[24] = {
      { (MOVE) { 0, 0, 0 }, "L'" },
      { (MOVE) { 0, 0, 1 }, "L" },
      { (MOVE) { 0, 1, 0 }, "M'" },
      { (MOVE) { 0, 1, 1 }, "M" },
      { (MOVE) { 0, 2, 0 }, "R" },
      { (MOVE) { 0, 2, 1 }, "R'" },

      { (MOVE) { 0, 3, 0 }, "x" },
      { (MOVE) { 0, 3, 1 }, "x'" },

      { (MOVE) { 1, 0, 0 }, "U'" },
      { (MOVE) { 1, 0, 1 }, "U" },
      { (MOVE) { 1, 1, 0 }, "E'" },
      { (MOVE) { 1, 1, 1 }, "E" },
      { (MOVE) { 1, 2, 0 }, "D" },
      { (MOVE) { 1, 2, 1 }, "D'" },

      { (MOVE) { 1, 3, 0 }, "y'" },
      { (MOVE) { 1, 3, 1 }, "y" },

      { (MOVE) { 2, 0, 0 }, "F" },
      { (MOVE) { 2, 0, 1 }, "F'" },
      { (MOVE) { 2, 1, 0 }, "S'" },
      { (MOVE) { 2, 1, 1 }, "S" },
      { (MOVE) { 2, 2, 0 }, "B'" },
      { (MOVE) { 2, 2, 1 }, "B" },

      { (MOVE) { 2, 3, 0 }, "z" },
      { (MOVE) { 2, 3, 1 }, "z'" },
  };

  MOVES* testStep(int step_num, unsigned char* parts, MOVE* last = 0, MOVE* last2 = 0);

  void store();

  void load();

  MOVES* addMoves(const MOVE move, MOVES* moves, bool begin = true);

  MOVES* simplifyMoves(MOVES*&moves, bool second = false);
//  char *prepareNumber(int x);

public:
  Tester(unsigned char* parts);

  long getSteps() { return this->steps; }

  MOVES* test(unsigned char steps);

  void move2str(MOVE move, char*);

  char* move2str(MOVE move);

  char* moves2str(MOVES* moves, const char* separator = "");

  /*static void int2move(unsigned char i, MOVE &m) {
    m.axis = (unsigned char) ((i >> 2));
    m.pos = (unsigned char) (i & 2);
    m.dir = (i & 1) != 0;
  }

  static MOVE int2move(unsigned char i) {
    MOVE m;
    m.axis = (unsigned char) ((i >> 2));
    m.pos = (unsigned char) (i & 2);
    m.dir = (i & 1) != 0;
    return m;
  }//*/
};

#include "tester.h"

#endif //CUBE_TESTER_H
