#include "square.h"

int max(int a, int b) {
  return (a > b) ? a : b;
}

int min(int a, int b) {
  return (a < b) ? a : b;
}

Square::Square(int r, int c) {
  row = min(max(r, 1), 8);
  col = min(max(c, 1), 8);
}

int Square::get_row(void) {
  return row;
}

int Square::get_col(void) {
  return col;
}

void Square::set_row(int r) {
  row = min(max(r, 1), 8);
}

void Square::set_col(int c) {
  col = min(max(c, 1), 8);
}

bool Square::operator==(Square &other) {
  return (this->get_col() == other.get_col()) && (this->get_row() == other.get_row());
}

bool Square::operator!=(Square other) {
  return !this->operator==(other);
}

Square::~Square(void) {}
