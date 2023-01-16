#include "guimoves.h"
#include <iostream>

GUIMoves::GUIMoves(std::shared_ptr<Board> b)
  : GUIElem(b)
{
  if(TTF_Init() != 0) {
    exit(1);
  }
  this->f = TTF_OpenFont("assets/fonts/FreeSerif.ttf", 12);
}

void GUIMoves::load_assets(SDL_Renderer *r) {
  return;
}

void GUIMoves::handle(SDL_Renderer *r) {
  std::cout << "This function is called" << std::endl;
  SDL_RenderSetViewport(r, viewport);
  auto text_surface = TTF_RenderText_Solid_Wrapped(f, "Helloaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", { 128, 128, 128, 255 }, 300);
  auto text_texture = SDL_CreateTextureFromSurface(r, text_surface);
  SDL_Rect rect = {0, 0, viewport->w, viewport->h};
  SDL_RenderCopy(r, text_texture, NULL, &rect);
  SDL_RenderPresent(r);
  return;
}

void GUIMoves::update(SDL_Renderer *r) {
  // remove this line
  this->handle(r);
  return;
}

GUIMoves::~GUIMoves(void) {
  TTF_CloseFont(f);
  TTF_Quit();
}
