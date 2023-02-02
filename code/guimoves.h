#ifndef GUIMOVES_H_
#define GUIMOVES_H_

#include "guielem.h"
#include "SDL_ttf.h"

class GUIMoves : public GUIElem {
  TTF_Font *reg; // regular font
  TTF_Font *bold; // bold font
  struct Node {
    SDL_Texture *t;
    std::shared_ptr<const Move> m;
    std::shared_ptr<Node> parent;
    int next_node_idx = -1;
    std::vector<std::shared_ptr<Node>> children;
  };
  std::shared_ptr<Node> root;
  public:
  GUIMoves(std::shared_ptr<Board> b);
  void load_assets(SDL_Renderer *r) override;
  void handle(SDL_Renderer *r, SDL_Event *e) override;
  void update(SDL_Renderer *r) override;
  ~GUIMoves(void);
};

#endif
