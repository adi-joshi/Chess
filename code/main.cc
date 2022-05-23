#include "game.h"

#if DEBUG != 1

int main(void) {
  Game *g = new Game();
  g->play();
  delete g;
  return 0;
}

#else

#endif
