#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "move.h"
#include "piece.h"
#include "result.h"
#include "exception.h"
#include "color.h"


class Display {
  public:
  Display();
  virtual void welcome_msg() = 0;
  virtual std::shared_ptr<Move> ask_move(Color turn) = 0;
  // called by observer (i.e. Board, after verifying that move is valid)
  virtual void clear_board() = 0;
  virtual std::string draw_board(std::vector<Piece*>::const_iterator begin,
                  std::vector<Piece*>::const_iterator end) = 0;
  virtual void print_board() = 0;
  virtual void print_moves(std::vector<std::shared_ptr<Move>>::const_iterator begin,
                   std::vector<std::shared_ptr<Move>>::const_iterator end) = 0;
  virtual void print_error(Exception e) = 0;
  virtual void print_winner(Result r) = 0;
  ~Display();
};

#endif
