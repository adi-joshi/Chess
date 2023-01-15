#ifndef GUIBOARD_H_
#define GUIBOARD_H_

#include "guielem.h"

class GUIBoard : public GUIElem {
  struct ScreenPos {
    int x;
    int y;
  };
  std::map<std::pair<Color, PieceName>, SDL_Texture*> piece_textures;
  std::vector<std::tuple<Color, PieceName, ScreenPos>> positions;
  SDL_Texture *board;
  void draw_board(SDL_Renderer *r);
  SDL_Rect board_drawing_specs(void);
  public:
  GUIBoard(std::shared_ptr<Board> b);
  void handle(SDL_Renderer *r) override;
  void load_assets(SDL_Renderer *r) override;
  void update(SDL_Renderer *r) override;
  ~GUIBoard(void);
};

#endif
