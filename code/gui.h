#ifndef GUI_H_
#define GUI_H_

#include <vector>
#include <tuple>
#include <map>
#include "SDL.h"
#include "display.h"

class GUI : public Display {
  const int win_w;
  const int win_h;
  SDL_Window *window;
  SDL_Surface *board;
  std::map<std::pair<Color, PieceName>, SDL_Surface*> piece_surfaces;
  std::vector<std::tuple<Color, PieceName, Square>> positions;
  public:
  GUI();
  void welcome_msg() override;
  Move *ask_move(Color turn) override;
  // called by observer (i.e. Board, after verifying that move is valid)
  void clear_board() override;
  std::string draw_board(std::vector<Piece*>::const_iterator begin,
                  std::vector<Piece*>::const_iterator end) override;
  void print_board() override;
  void print_moves(std::vector<Move*>::const_iterator begin,
                   std::vector<Move*>::const_iterator end) override;
  void print_error(Exception e) override;
  void print_winner(Result r) override;
  ~GUI();
};

#endif
