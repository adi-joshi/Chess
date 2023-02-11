#ifndef GUIMOVES_H_
#define GUIMOVES_H_

#include "guielem.h"
#include "SDL_ttf.h"

class GUIMoves : public GUIElem {
  TTF_Font *reg; // regular font
  TTF_Font *bold; // bold font
  struct Node {
    SDL_Texture *t;
    SDL_Rect position;
    std::shared_ptr<const Move> m;
    std::shared_ptr<Node> parent;
    int next_node_idx = -1;
    std::vector<std::shared_ptr<Node>> children;
  };
  std::shared_ptr<Node> root;
  // box is a pair of x and y indicating where this function should
  // start drawing the subvariation.
  // The return value is the size of the box (in w, h) of where the
  // function drew, for e.g. if what was printed by
  // recurse_subvariations is:
  // 1. e4 e5 2. Nf3 Nc6 3. Bg4 |
  //       d5 2. Nc3            | h
  //          2. exd5           |
  // -------------------------->v
  //             w           
  void find_drawing_rectangles(SDL_Renderer *r);
  public:
  GUIMoves(std::shared_ptr<Board> b);
  void load_assets(SDL_Renderer *r) override;
  void handle(SDL_Renderer *r, SDL_Event *e) override;
  void update(SDL_Renderer *r) override;
  ~GUIMoves(void);
};

#endif
