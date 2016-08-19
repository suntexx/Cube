
#ifndef CUBE_CUBE_H
#define CUBE_CUBE_H

class Cube {
private:
  void reset();

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

protected:
  short* parts;
//  short parts[54];

  short* clone(short* parts, short* res = 0);

  void removeClone(short*&parts);

  void setSquare(short id, short val);

public:
  Cube();

  char* move2str(MOVE move);

  char* moves2str(MOVES* moves, const char* separator = "");

  short* setValues(short* parts);

  void setValues(char* parts);

  short* getValues();

  short* getValues(short* destination);

  static short mapX(short square, short position, short z);

  void rotateX(short pos, bool dir);

  void rotateXFull(bool dir);

  static short mapY(short square, short position, short z);

  void rotateY(short pos, short dir);

  void rotateYFull(bool dir);

  static short mapZ(short square, short position, short z);

  void rotateZ(short pos, bool dir);

  void rotateZFull(bool dir);

  void rotateSide(short sq, bool dir);

  bool isSolved(short* parts = 0);

  void rotate(short axis, short pos, bool dir);

  void rotate(MOVE move);

  void rotate(short i);

  static short getSquareNumID(short sq, short num);

  void toString(char* str, short* parts = 0);

  void shuffle(int);

  /*short getColor(short id);

  short getColorNum(short sq, short num);

  short getColorXY(short sq, short x, short y);

  static short id2square(short id);

  static short id2col(short id);

  static short id2row(short id);

  static short getSquareXYID(short sq, short x, short y);*/
  /*
  static void log();

  template<typename ...Rest>
  static void log(int i, Rest...);

  template<typename ...Rest>
  static void log(short s, Rest...);

  template<typename ...Rest>
  static void log(float f, Rest...);

  template<typename ...Rest>
  static void log(char const* c, Rest...);

  template<typename T, typename ...Rest>
  static void log(T c, Rest...);

  template<typename ...Rest>
  static void log(Rest... rest);

  / * /
  template<typename T>
  static void log(T const &t);

  template<typename First, typename ... Rest>
  static void log(First const &first, Rest const &... rest);//*/
};

#endif //CUBE_CUBE_H
