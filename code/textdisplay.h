#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include <array>
#include <vector>
#include <string>
#include "display.h"

class TextDisplay : public Display {
  std::array<std::array<std::string, 8>, 8> board;
  public:
  TextDisplay();
  void welcome_msg() override;
  std::shared_ptr<Move> ask_move(Color turn) override;
  // called by observer (i.e. Board, after verifying that move is valid)
  void clear_board() override;
  std::string draw_board(std::vector<Piece*>::const_iterator begin,
                  std::vector<Piece*>::const_iterator end) override;
  void print_board() override;
  void print_moves(std::vector<std::shared_ptr<Move>>::const_iterator begin,
                   std::vector<std::shared_ptr<Move>>::const_iterator end) override;
  void print_error(Exception e) override;
  void print_winner(Result r) override;
  ~TextDisplay();
};

#endif
