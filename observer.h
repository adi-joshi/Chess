#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>
#include "square.h"
#include "color.h"
#include "piecename.h"
#include "move.h"

class Observer {
  public:
  virtual void notify(Square from, Square to, Color c, PieceName p) = 0;
  virtual void print_moves(std::vector<Move>::iterator it) = 0;
};

#endif
