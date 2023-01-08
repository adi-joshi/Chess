#include "game.h"
#include "exception.h" // exception file
#include "result.h" // enumeration of Black, White or Draw
#include "textdisplay.h"
#include "gui.h"
#include <iostream>

Game::Game(std::string display) {
  if (display == "gui") {
    td = std::make_shared<GUI>();
  } else {
    td = std::make_shared<TextDisplay>();
  }
  b = std::make_shared<Board>(td);
  b->setup_board();
  turn = Color::White;
}

void Game::play(void) {
  td->welcome_msg();
  td->print_board();
  while(!b->game_end()) {
    try {
      auto s = td->ask_move(turn);
      if (s == nullptr) {
	      continue;
      } else if (s->it == InputType::Quit) {
	return;
      }
      bool moved = b->move(s);
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

Game::~Game(void) {}
