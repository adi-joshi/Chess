#ifndef GUI_H_
#define GUI_H_

#include <vector>
#include <tuple>
#include <map>
#include "SDL.h"
#include "display.h"
#include "guiboard.h"
#include "guimoves.h"

class GUI : public Display {
  int win_w;
  int win_h;
  SDL_Window *window;
  SDL_Renderer *winren;
  std::shared_ptr<Board> b;
  std::shared_ptr<GUIBoard> gb;
  std::shared_ptr<GUIMoves> gm;
  public:
  GUI(std::shared_ptr<Board> b);
  void handle_input(void);
  /*
  void welcome_msg() override;
  std::shared_ptr<Move> ask_move(Color turn) override;
  // called by observer (i.e. Board, after verifying that move is valid)
  void clear_board() override;
  void draw_board(std::vector<std::shared_ptr<Piece>>::const_iterator begin,
                  std::vector<std::shared_ptr<Piece>>::const_iterator end) override;
  void print_board() override;
  void print_moves(std::vector<std::shared_ptr<Move>>::const_iterator begin,
                   std::vector<std::shared_ptr<Move>>::const_iterator end) override;
  void print_winner(Result r) override;
  */
  void print_error(Exception e) override;
  ~GUI();
};

#endif
