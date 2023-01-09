#ifndef GUI_H_
#define GUI_H_

#include <vector>
#include <tuple>
#include <map>
#include "SDL.h"
#include "display.h"

class GUI : public Display {
  struct ScreenPos {
    int x;
    int y;
  };
  const int win_w;
  const int win_h;
  SDL_Renderer *winren;
  SDL_Texture *board;
  std::map<std::pair<Color, PieceName>, SDL_Texture*> piece_textures;
  std::vector<std::tuple<Color, PieceName, ScreenPos>> positions;
  public:
  GUI();
  void welcome_msg() override;
  std::shared_ptr<Move> ask_move(Color turn) override;
  // called by observer (i.e. Board, after verifying that move is valid)
  void clear_board() override;
  void draw_board(std::vector<std::shared_ptr<Piece>>::const_iterator begin,
                  std::vector<std::shared_ptr<Piece>>::const_iterator end) override;
  void print_board() override;
  void print_moves(std::vector<std::shared_ptr<Move>>::const_iterator begin,
                   std::vector<std::shared_ptr<Move>>::const_iterator end) override;
  void print_error(Exception e) override;
  void print_winner(Result r) override;
  ~GUI();
};

#endif
