#include "move.h"

Move::Move(Color c, PieceName p, Square src, Square dst)
  : c{c}, p{p}, src{src}, dst{dst}
{}

Move::Move(Color c, PieceName p, Square src, Square dst, std::string suff)
  : c{c}, p{p}, src{src}, dst{dst}, suff{suff}
{}

Color Move::get_color(void) {
  return c;
}

PieceName Move::get_piecename(void) {
  return p;
}

Square Move::get_src(void) {
  return src;
}

Square Move::get_dst(void) {
  return dst;
}

std::string Move::get_suff(void) {
  return suff;
}

Move::~Move(void) {}
