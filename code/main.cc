#include <string>
#include "game.h"

#if DEBUG != 1

int main(int argc, char **argv) {
  std::string display = "tui";
  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '-' && argv[i][1] == 'g') {
      display = "gui";
    } else if (argv[i][0] == '-' && argv[i][1] == 't') {
      display = "tui";
    }
  }
  Game *g = new Game(display);
  g->play();
  delete g;
  return 0;
}

#else

#endif
