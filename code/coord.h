#ifndef COORD_H_
#define COORD_H_

class Coord {
  int row;
  int col;
  public:
  Coord(int r, int c);
  int get_row();
  int get_col();
  void set_row(int r);
  void set_col(int c);
  bool operator==(Coord &other);
  bool operator!=(Coord other);
  ~Coord();
};

#endif
