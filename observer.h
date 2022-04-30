#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "square.h"
#include "color.h"
#include "piecename.h"

class Observer {
  public:
  virtual void notify(Square from, Square to, Color c, PieceName p) = 0;
};

#endif
