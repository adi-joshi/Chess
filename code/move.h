#ifndef MOVE_H_
#define MOVE_H_

#include "color.h"
#include "piecename.h"
#include "square.h"
#include <tuple>
#include <vector>
#include <string>
#include <memory>

// typename Move std::tuple<Color, std::pair<PieceName, Square>, std::pair<PieceName, Square>, std::string>; // want this

// typedef std::pair<Color, std::pair<std::pair<PieceName, Square>, std::pair<PieceName, Square>>> PieceMove;

enum class InputType { Move, Print };

enum class MoveType {
  Unknown,
  Normal,
  Capture,
  EnPassant,
  Promotion,
  Castling,
};

class Piece;

struct Move {
  InputType it;
  MoveType mt = MoveType::Unknown;
  Color color;
  std::shared_ptr<Square> from;
  std::shared_ptr<Square> to;
  PieceName piecename;
  std::string pref; // prefix
  PieceName promoted_to;
  std::string error_str = "";
  std::vector<std::vector<std::shared_ptr<Piece>>::iterator> pieces_to_capture;

  /*
  Move(Color c, Square from, Square to); // For UCI notation, e.g. e2e4
  Move(Color c, Square from, Square to, PieceName promotion); // for pawn promotion, e.g. e7e8=Q
  Move(Color c, Square to, PieceName promotion); // SAN promotion
  Move(Color c, PieceName p, Square to); // For SAN notation e.g. e4
  */
};


/*
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
*/

#endif
