#ifndef MOVE_H_
#define MOVE_H_

#include "color.h"
#include "piecename.h"
#include "square.h"
#include <tuple>
#include <string>

// typename Move std::tuple<Color, std::pair<PieceName, Square>, std::pair<PieceName, Square>, std::string>; // want this


class Move {
  std::tuple<Color, std::pair<PieceName, Square>, std::pair<PieceName, Square>, std::string> move_comps;
  // The above is the same as
  // std::tuple<color, std::pair<piece_before_move, square_before_move>, std::pair<piece_after_move, square_after_move>, suffix>
  // where
  // - suffix: is the suffix for notation (i.e. if Knights are on g3 and c3, then Ne4 should be Nge4. The suffix here is 'g').

  public:
  Move(Color c, PieceName src_p, Square src, PieceName dst_p, Square dst, std::string suff);
  Color get_color();
  PieceName get_src_piecename();
  Square get_src_square();
  PieceName get_dst_piecename();
  Square get_dst_square();
  std::string get_suffix();
  ~Move();
};

#endif
