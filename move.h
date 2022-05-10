#ifndef MOVE_H_
#define MOVE_H_

#include "color.h"
#include "piecename.h"
#include "square.h"
#include <tuple>
#include <string>


class Move {
  Color c;
  PieceName p;
  Square src;
  Square dst;
  std::string suff; // is the suffix for notation (i.e. if Knights are on g3 and c3, then Ne4 should be Nge4. The suffix here is 'g').

  public:
  Move(Color c, PieceName p, Square src, Square dst);
  Move(Color c, PieceName p, Square src, Square dst, std::string suff);
  Color get_color();
  PieceName get_piecename();
  Square get_src();
  Square get_dst();
  std::string get_suff();
  ~Move();
};

#endif
