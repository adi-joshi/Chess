#ifndef MOVE_H_
#define MOVE_H_

#include "color.h"
#include "piecename.h"
#include "square.h"
#include <tuple>
#include <vector>
#include <string>
#include <memory>

enum class InputType { Move, Print, Quit };

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
  std::string board_string;
};

#endif
