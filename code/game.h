#ifndef GAME_H_
#define GAME_H_

#include "board.h"
#include "textdisplay.h"
#include "color.h" // enumeration of Black or White

class Game {
  Board *b;
  TextDisplay *td;
  Color turn;
  public:
  Game();
  void play();
  ~Game();
};

#endif
