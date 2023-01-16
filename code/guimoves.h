#ifndef GUIMOVES_H_
#define GUIMOVES_H_

#include "guielem.h"
#include "SDL_ttf.h"

class GUIMoves : public GUIElem {
  TTF_Font *f;
  public:
  GUIMoves(std::shared_ptr<Board> b);
  void load_assets(SDL_Renderer *r) override;
  void handle(SDL_Renderer *r) override;
  void update(SDL_Renderer *r) override;
  ~GUIMoves(void);
};

#endif
