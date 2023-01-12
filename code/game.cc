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
  b = std::make_shared<Board>();
  b->setup_board();
  auto begin = b->get_pieces_cbegin();
  auto end = b->get_pieces_cend();
  td->draw_board(begin, end);
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
        auto begin = b->get_pieces_cbegin();
        auto end = b->get_pieces_cend();
        td->draw_board(begin, end);
      }
    } catch (Exception &e) {
      td->print_error(e);
    }
    td->print_board();
  }
  td->print_winner(b->winner());
  return;
}

Game::~Game(void) {}
