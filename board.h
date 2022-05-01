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
#include "move.h"



class Board : public Subject {
  // vector <Object *> ob is in Subject class
  protected:
  std::vector<Piece *> pieces;

  // Stores one move as ({from, name, color}, {to, name, color})
  // e.g. if you play e7e8=Q, then it would be stored as
  // ({e7, Pawn, White}, {e8, Queen, White}).
  std::vector<Move> moves;

  public:
  Board(TextDisplay *td);
  bool move(std::string s, Color turn);
  bool game_end();
  Result winner();
  friend class Piece; // any piece can get the pieces vector and the moves vector by this
};

#endif
