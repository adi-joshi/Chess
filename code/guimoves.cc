#include "guimoves.h"
#include "SDL_ttf.h"

GUIMoves::GUIMoves(std::shared_ptr<Board> b)
  : GUIElem(b)
{}

void GUIMoves::load_assets(SDL_Renderer *r) {
  return;
}

void GUIMoves::handle(SDL_Renderer *r) {
  return;
}

GUIMoves::~GUIMoves(void) {
}
