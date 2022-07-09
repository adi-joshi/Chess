#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <map>
#include <utility>
#include <tuple>
#include <string>
#include "display.h"
#include "result.h"
#include "piece.h"
#include "move.h"

class Board : public std::enable_shared_from_this<Board> { // so that can send shared_ptr<Board> to pieces
  // vector <Object *> ob is in Subject class
  std::shared_ptr<Display> td;
  std::vector<Piece *> pieces;
  std::vector<std::shared_ptr<Move>> moves;
  std::map<std::string, int> board_string; // map<board_string, # times it occured> (for 3fold)
  int halfmoves = 0; // the number of moves without a pawn move or capture
  // Stores one move as ({from, name, color}, {to, name, color})
  // e.g. if you play e7e8=Q, then it would be stored as
  // ({e7, Pawn, White}, {e8, Queen, White}).
  public:
  Board(std::shared_ptr<Display> td);

  // can't setup pieces in constructor, and can't use shared_from_this() in constructor
  void setup_board();
  void setup_board(std::vector<Piece *> pieces);
  bool move(std::shared_ptr<Move> m);
  std::shared_ptr<Move> get_prev_move();
  bool game_end();
  Result winner();
  friend class Piece; // any piece can get the pieces vector and the moves vector by this
  ~Board();
};

#endif
