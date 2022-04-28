#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <utility>
#include <tuple>
#include <string>
#include "subject.h"
#include "textdisplay.h"
#include "result.h"
#include "piece.h"


class Board : public Subject {
  // vector <Object *> ob is in Subject class
  protected:
  std::vector<Piece *> pieces;

  // Stores one move as ({from, name, color}, {to, name, color})
  // e.g. if you play e7e8=Q, then it would be stored as
  // ({e7, Pawn, White}, {e8, Queen, White}).
  std::vector<std::pair<std::tuple<Square, PieceName, Color>, std::tuple<Square, PieceName, Color>>> moves;

  public:
  Board(TextDisplay *td);
  void move(std::string s);
  bool game_end();
  Result winner();
  friend class Piece; // any piece can get the pieces vector and the moves vector by this
};

#endif
