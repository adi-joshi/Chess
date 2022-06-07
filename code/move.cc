#include "move.h"

/*
Move::Move(Color c, Square from, Square to)
  : turn{c}, from{from}, to{to}
{}

Move::Move(Color c, Square from, Square to, PieceName promotion)
  : turn{c}, from{from}, to{to}, promoted_to{promotion}
{}

Move::Move(Color c, Square to, PieceName promotion)
  : turn{c}, to{to}, promoted_to{promotion}
{}

Move::Move(Color c, PieceName p, Square to)
  : turn{c}, piecename{p}, to{to}
{}
*/

/*
Move::Move(Color c, PieceName src_p, Square src, PieceName dst_p, Square dst, std::string suff)
  : move_comps{c, {src_p, src}, {dst_p, dst}, suff}
{}


Color Move::get_color(void) {
  return std::get<0>(move_comps);
}

PieceName Move::get_src_piecename(void) {
  return std::get<1>(move_comps).first;
}

Square Move::get_src_square(void) {
  return std::get<1>(move_comps).second;
}

PieceName Move::get_dst_piecename(void) {
  return std::get<2>(move_comps).first;
}

Square Move::get_dst_square(void) {
  return std::get<2>(move_comps).second;
}

std::string Move::get_suffix(void) {
  return std::get<3>(move_comps);
}

Move::~Move(void) {}
*/
