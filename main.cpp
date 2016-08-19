#include <iostream>
#include <stdlib.h>
#include <cmath>

#include "global.h"
#include "cube.h"
#include "tester.h"

#ifdef NDEBUG
#define MAX_DEPTH 7
#define RANDOM_STEPS 999
#else
#define MAX_DEPTH 6
#define RANDOM_STEPS 3//(MAX_DEPTH)
#endif

// BEST TIME FOR:
// x7 = 5.03735s // w/o backsteps 3.76231 (22.510.104 <- 23.384.604 <- 39.089.244)
// x8 = 60.7934s // w/o bs 39.1882 (245.722.104 <- 257.230.656 <- 469.070.940)

const MOVE operator !(const MOVE &a) { return (MOVE) { a.axis, a.pos, !a.dir }; }

bool operator ==(const MOVE &a, const MOVE &b) { return a.axis == b.axis && a.pos == b.pos && a.dir == b.dir; }

bool operator !=(const MOVE &a, const MOVE &b) { return a.axis != b.axis || a.pos != b.pos || a.dir != b.dir; }

bool operator ==(const MOVES &a, const MOVES &b) {
  if (a.count != b.count) return false;

  for (int i = 0; i < a.count; i++) if (a.moves[i] != b.moves[i]) return false;

  return true;
}

bool operator !=(const MOVES &a, const MOVES &b) { return !(a == b); }

int main() {
  srand(clock());

  Cube* cube = new Cube();

#ifdef NDEBUG
  std::cout << "Release" << std::endl;
#else
  std::cout << "Debug" << std::endl;
#endif

#ifndef RANDOM_STEPS
  //  char str[] = "333000000011011011222222222335335335444444444555555111"; // 3
    char str[] = "220000003044111111112220220533233233433444444551555555"; // 3
  //  char str[] = "333004114445015011221221000032035335555443443222552411"; // 4
  //  char str[] = "012403441413411215552025224051230004553243103331254035"; // 8
  //  char str[] = "433000114025015055225323323140031042241541341434255215"; // 10
  //  char str[] = "435400122012012445033025115044334224301341355223555110"; // 5
    cube->setValues(str);
#endif

  int i, x;

  for (i = MAX_DEPTH + 1, x = 0; --i;) x += pow(12, i);

#ifdef RANDOM_STEPS
  std::cout << "shuffling: " << RANDOM_STEPS << " | ";
  cube->shuffle(RANDOM_STEPS);
#endif

  char state[55] = { 0 };
  cube->toString(state);
  std::cout << "depth: " << MAX_DEPTH << " | combinations: " << x << " | state: " << state << std::endl;
//  Cube::log("depth", MAX_DEPTH, "variants", x, "state", state, "\n");

  Tester* tester = new Tester(cube->getValues());
  MOVES* moves = tester->test(MAX_DEPTH);

  if (moves) {
    char* str = 0;
    std::cout << "result: " << (str = cube->moves2str(moves, " ")) << std::endl;
    delete[] str;
    /*for (i = 0; i < moves->count; i++) {
  //      tester->move2str(moves->moves[i], m);
  //      std::cout << m;
        if ((str = cube->move2str(moves->moves[i])) != 0) std::cout << str << " ";
      }//*/
//    std::cout << "[" << moves << "]" << std::endl;
  }
  else std::cout << "not found | " << tester->getSteps() << std::endl;

//  for (i = 0; i < 100; i++) std::cout << random(1, 10);

  return 0;
}