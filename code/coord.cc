#include "coord.h"

int max(int a, int b) {
  return (a > b) ? a : b;
}

int min(int a, int b) {
  return (a < b) ? a : b;
}

Coord::Coord(int r, int c) {
  row = min(max(r, 1), 8);
  col = min(max(c, 1), 8);
}

int Coord::get_row(void) {
  return row;
}

int Coord::get_col(void) {
  return col;
}

void Coord::set_row(int r) {
  row = min(max(r, 1), 8);
}

void Coord::set_col(int c) {
  col = min(max(c, 1), 8);
}

bool Coord::operator==(Coord &other) {
  return (this->get_col() == other.get_col()) && (this->get_row() == other.get_row());
}

bool Coord::operator!=(Coord other) {
  return !this->operator==(other);
}

Coord::~Coord(void) {}
