#include "game.h"
#include "exception.h" // exception file
#include "result.h" // enumeration of Black, White or Draw

Game::Game(void) {
  td = new TextDisplay();
  b = new Board(td);
  turn = Color::White;
}

void Game::play(void) {
  td->welcome_msg();
  td->print_board();
  while(!b->game_end()) {
    try {
      auto s = td->ask_move(turn);
      bool moved = b->move(s, turn); // board and textdisplay are in subject observer pattern, so if b->move(s, turn) is valid, it automatically changes the board in textdisplay
      if (moved) {
	turn = static_cast<Color>((static_cast<int>(turn) + 1) % 2);
      }
      td->print_board();
    } catch (Exception &e) {
      td->print_error(e);
    }
  }
  td->print_winner(b->winner());
  return;
}

Game::~Game(void) {
  delete b;
  delete td;
}
