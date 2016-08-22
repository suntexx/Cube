#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

#include "global.h"
#include "cube.h"
#include "tester.h"

#ifdef NDEBUG
#define METHOD_FASTEST 1
#define MAX_DEPTH 7
#define RANDOM_STEPS 999
#else
#define MAX_DEPTH 5
#define RANDOM_STEPS (MAX_DEPTH)
#endif

// BEST TIME FOR:
// x7 = 5.03735s // w/o backsteps 2.74905 (22.510.104 <- 23.384.604 <- 39.089.244)
// x8 = 60.7934s // w/o bs 28.1782 (245.722.104 <- 257.230.656 <- 469.070.940)
// x9            // w/o bs 288.44 (2.682.322.104 <- <- 5.628.851.292)

const MOVE operator !(const MOVE &a) { return (MOVE) { a.axis, a.pos, !a.dir }; }

bool operator ==(const MOVE &a, const MOVE &b) { return a.axis == b.axis && a.pos == b.pos && a.dir == b.dir; }

bool operator !=(const MOVE &a, const MOVE &b) { return a.axis != b.axis || a.pos != b.pos || a.dir != b.dir; }

bool operator ==(const MOVES &a, const MOVES &b) {
  if (a.count != b.count) return false;

  for (int i = a.count; i--;) if (a.moves[i] != b.moves[i]) return false;

  return true;
}

bool operator !=(const MOVES &a, const MOVES &b) { return !(a == b); }

class comma_numpunct : public std::numpunct<char> {
protected:
  virtual char do_thousands_sep() const { return ','; }

  virtual std::string do_grouping() const { return "\03"; }
};

template<typename T>
std::string FormatWithCommas(T value) {
  std::stringstream ss;
  std::locale comma_locale(std::locale(),
  new comma_numpunct());
  ss.imbue(comma_locale);

  ss << std::fixed << value;
  return ss.str();
}

MOVE int2move(unsigned char i) {
  MOVE m;
  m.axis = (unsigned char) ((i >> 2));
  m.pos = (unsigned char) (i & 2);
  m.dir = (i & 1) != 0;
  return m;
}

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
  char str[] = "000000334110110220223223223533533544444444111112555555"; // 3
  //  char str[] = "333004114445015011221221000032035335555443443222552411"; // 4
  //  char str[] = "012403441413411215552025224051230004553243103331254035"; // 8
  //  char str[] = "433000114025015055225323323140031042241541341434255215"; // 10
  //  char str[] = "435400122012012445033025115044334224301341355223555110"; // 5
  cube->setValues(str);
#endif

  int i;
  long x;

  for (i = MAX_DEPTH + 1, x = 0; --i;) x += pow(12, i);

#ifdef RANDOM_STEPS
  std::cout << "shuffling: " << RANDOM_STEPS << " | ";
  cube->shuffle(RANDOM_STEPS);
#endif

  char state[55] = { 0 };
  cube->toString(state);

  std::cout << "depth: " << MAX_DEPTH << " | combinations: " << FormatWithCommas(x) << " | state: " << state << std::endl;

  Tester* tester = new Tester(cube->getValues());
  MOVES* moves = tester->test(MAX_DEPTH);

  if (moves) {
    char* str = 0;
    std::cout << "result: " << (str = tester->moves2str(moves, " ")) << std::endl;
    delete[] str;
  }
  else std::cout << "not found | " << FormatWithCommas(tester->getSteps()) << " (-" << FormatWithCommas(x - tester->getSteps()) << ")" << std::endl;

  return 0;
}