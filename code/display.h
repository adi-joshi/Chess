#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "move.h"
#include "piece.h"
#include "result.h"
#include "exception.h"
#include "color.h"
#include "board.h"

class Display {
  protected:
  std::shared_ptr<Board> b;
  public:
  Display(std::shared_ptr<Board> b);
  virtual void handle_input(void) = 0;
  virtual void print_error(Exception e) = 0;
  /*
  virtual void welcome_msg() = 0;
  virtual std::shared_ptr<Move> ask_move(Color turn) = 0;
  // called by observer (i.e. Board, after verifying that move is valid)
  virtual void clear_board() = 0;
  virtual void draw_board(std::vector<std::shared_ptr<Piece>>::const_iterator begin,
                  std::vector<std::shared_ptr<Piece>>::const_iterator end) = 0;
  virtual void print_board() = 0;
  virtual void print_moves(std::vector<std::shared_ptr<Move>>::const_iterator begin,
                   std::vector<std::shared_ptr<Move>>::const_iterator end) = 0;
  virtual void print_winner(Result r) = 0;
  */
  ~Display();
};

#endif
