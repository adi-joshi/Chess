#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include <array>
#include <vector>
#include <string>
#include "square.h"
#include "piecename.h"
#include "color.h"
#include "exception.h"
#include "result.h"
#include "move.h"
#include "piece.h"


class TextDisplay {
  std::array<std::array<char, 8>, 8> board;
  public:
  TextDisplay();
  void welcome_msg();
  std::string ask_move(Color turn);
  // called by observer (i.e. Board, after verifying that move is valid)
  void clear_board();
  void draw_board(std::vector<Piece*>::const_iterator begin,
                  std::vector<Piece*>::const_iterator end);
  void print_board();
  void print_moves(std::vector<Move*>::const_iterator begin,
                   std::vector<Move*>::const_iterator end);
  void print_error(Exception e);
  void print_winner(Result r);
  ~TextDisplay();
};

#endif
