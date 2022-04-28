#ifndef SQUARE_H_
#define SQUARE_H_

class Square {
  int row;
  int col;
  public:
  Square(int r, int c);
  int get_row();
  int get_col();
  void set_row(int r);
  void set_col(int c);
  bool operator==(Square &other);
  ~Square();
};

#endif
