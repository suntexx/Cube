
#ifndef CUBE_CUBE_H
#define CUBE_CUBE_H

class Cube {
private:
  void reset();

protected:
  unsigned char* parts;

  void setSquare(unsigned char id, unsigned char val);

public:
  unsigned char* clone(unsigned char* parts, unsigned char* res = 0);

  void removeClone(unsigned char*&parts);

  Cube();

  Cube(unsigned char* parts);

  unsigned char* setValues(unsigned char* parts);

  void setValues(char* parts);

  unsigned char* getValues();

  unsigned char* getValues(unsigned char* destination);

  static unsigned char mapX(unsigned char square, unsigned char position, unsigned char z);

  static unsigned char mapY(unsigned char square, unsigned char position, unsigned char z);

  static unsigned char mapZ(unsigned char square, unsigned char position, unsigned char z);

private:
  void rotateX(unsigned char pos, bool dir);

  void rotateXFull(bool dir);

  void rotateY(unsigned char pos, unsigned char dir);

  void rotateYFull(bool dir);

  void rotateZ(unsigned char pos, bool dir);

  void rotateZFull(bool dir);

  void rotateSide(unsigned char sq, bool dir);

public:
  bool isSolved(unsigned char* parts = 0);

  void rotate(unsigned char axis, unsigned char pos, bool dir);

  void rotate(MOVE move);

  void rotate(unsigned char i);

  static unsigned char getSquareNumID(unsigned char sq, unsigned char num);

  void toString(char* str, unsigned char* parts = 0);

  void shuffle(int);

  /*unsigned char getColor(unsigned char id);

  unsigned char getColorNum(unsigned char sq, unsigned char num);

  unsigned char getColorXY(unsigned char sq, unsigned char x, unsigned char y);

  static unsigned char id2square(unsigned char id);

  static unsigned char id2col(unsigned char id);

  static unsigned char id2row(unsigned char id);

  static unsigned char getSquareXYID(unsigned char sq, unsigned char x, unsigned char y);*/
  /*
  static void log();

  template<typename ...Rest>
  static void log(int i, Rest...);

  template<typename ...Rest>
  static void log(unsigned char s, Rest...);

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
