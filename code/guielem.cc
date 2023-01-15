#include "guielem.h"

GUIElem::GUIElem(std::shared_ptr<Board> b)
  : b{b}
{
  this->viewport = new SDL_Rect();
}


SDL_Rect GUIElem::get_viewport(void) {
  return { viewport->x, viewport->y, viewport->w, viewport->h };
}

void GUIElem::set_viewport(SDL_Rect *vp) {
  viewport->x = vp->x;
  viewport->y = vp->y;
  viewport->w = vp->w;
  viewport->h = vp->h;
  return;
}

GUIElem::~GUIElem(void) {}
