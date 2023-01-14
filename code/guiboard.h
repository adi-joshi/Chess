#ifndef GUIBOARD_H_
#define GUIBOARD_H_

#include "guielem.h"

class GUIBoard : public GUIElem {
  public:
  using GUIElem::GUIElem;
  void handle(SDL_Renderer *r) override;
  void update(void) override;
  ~GUIBoard(void);
};

#endif
