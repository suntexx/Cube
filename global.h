
#ifndef CUBE_GLOBAL_H
#define CUBE_GLOBAL_H

#define MIN(a, b) (a > b ? b : a)
#define MAX(a, b) (a > b ? a : b)
#define random(a, b) (rand() % (MAX(a, b) - MIN(a, b)) + MIN(a, b))

#define CUBE_SIZE (sizeof(short) * 54)

struct MOVE {
  short axis;
  short pos;
  bool dir;
};
struct MOVES {
  short count;
  MOVE* moves;
};
struct MOVE_STR {
  MOVE move;
  char str[3];
};

const MOVE operator !(const MOVE &a);

bool operator ==(const MOVE &a, const MOVE &b);

bool operator !=(const MOVE &a, const MOVE &b);

bool operator ==(const MOVES &a, const MOVES &b);

bool operator !=(const MOVES &a, const MOVES &b);

#endif //CUBE_GLOBAL_H
