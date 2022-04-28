#include "game.h"

int main(void) {
  Game *g = new Game();
  g->play();
  delete g;
  return 0;
}
