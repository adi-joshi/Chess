#ifndef GAME_H_
#define GAME_H_

#include <string>
#include "board.h"
#include "display.h"
#include "color.h" // enumeration of Black or White

class Game {
  std::shared_ptr<Board> b;
  std::shared_ptr<Display> td;
  public:
  Game(std::string display);
  void play();
  ~Game();
};

#endif
