#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include <array>
#include <vector>
#include <string>
#include "display.h"
#include "movetree.h"

class TextDisplay : public Display {
  std::array<std::array<std::string, 8>, 8> board;
  void clear_board(void);
  void draw_board(std::vector<std::shared_ptr<Piece>>::const_iterator begin,
                  std::vector<std::shared_ptr<Piece>>::const_iterator end);
  void print_board(void);
  void print_moves(MoveTree::const_iterator begin,
                   MoveTree::const_iterator end);
  void print_winner(Result r);
  public:
  TextDisplay(std::shared_ptr<Board> b);
  void handle_input(void) override;
  void print_error(Exception e) override;
  ~TextDisplay();
};

#endif
