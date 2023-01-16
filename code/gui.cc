#include <iostream>
#include "gui.h"
#include "textdisplay.h"
#include "SDL_image.h"
#include "guiboard.h"
#include "guimoves.h"

GUI::GUI(std::shared_ptr<Board> b)
  : Display(b), win_w{800}, win_h{800}
{
  SDL_Init(SDL_INIT_EVERYTHING);
  //auto b = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  winren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  gb = std::make_unique<GUIBoard>(b);
  gb->load_assets(winren);
  SDL_Rect r = {0, 0, 400, 800};
  gb->set_viewport(&r);
  gb->update(winren);

  gm = std::make_unique<GUIMoves>(b);
  gm->load_assets(winren);
  r = {400, 0, 400, 800};
  gm->set_viewport(&r);
  gm->update(winren);
}

void GUI::handle_input(void) {
  while(1) {
    gb->handle(winren);
  }
}

void GUI::print_error(Exception e) {
  std::cout << e.error() << std::endl;
}

GUI::~GUI(void) {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(winren);
  SDL_Quit();
}
