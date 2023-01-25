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
  int id = -1;
  void draw_board(SDL_Renderer *r);
  SDL_Rect board_region;
  std::shared_ptr<Move> m;
  public:
  GUIBoard(std::shared_ptr<Board> b);
  void handle(SDL_Renderer *r, SDL_Event *e) override;
  void load_assets(SDL_Renderer *r) override;
  void update(SDL_Renderer *r) override;
  void set_viewport(SDL_Rect *vp) override;
  ~GUIBoard(void);
};

#endif
