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
  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
  window = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  if (window == NULL) {
    std::cout << SDL_GetError() << std::endl;
  }
  winren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(winren, 255, 255, 255, 255);
  SDL_RenderClear(winren);
  gb = std::make_shared<GUIBoard>(b);
  gb->load_assets(winren);
  SDL_Rect r = {0, 0, win_w / 2, win_h};
  gb->set_viewport(&r);
  gb->update(winren);

  gm = std::make_shared<GUIMoves>(b);
  gm->load_assets(winren);
  r = {win_w / 2, 0, win_w / 2, win_h};
  gm->set_viewport(&r);
  gm->update(winren);

  gb->add_observer(gm);
  gm->add_observer(gb);
}

void GUI::handle_input(void) {
  SDL_Event e;
  while(1) {
    SDL_WaitEvent(&e);
    switch (e.type) {
      case SDL_QUIT:
	goto outer;
	break;
      case SDL_WINDOWEVENT:
	switch(e.window.event) {
	  case SDL_WINDOWEVENT_RESIZED:
	    win_w = e.window.data1;
	    win_h = e.window.data2;
	    SDL_SetRenderDrawColor(winren, 255, 255, 255, 255);
	    SDL_RenderClear(winren);
	    SDL_Rect r = {0, 0, win_w / 2, win_h};
	    gb->set_viewport(&r);
	    r = {win_w / 2, 0, win_w / 2, win_h};
	    gm->set_viewport(&r);
	    gb->update(winren);
	    gm->update(winren);
	}
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEMOTION:
      case SDL_MOUSEBUTTONUP:
	gb->handle(winren, &e); break;
      case SDL_KEYDOWN:
	gm->handle(winren, &e); break;
      default: break;
    }
  }
outer:
  return;
}

void GUI::print_error(Exception e) {
  std::cout << e.error() << std::endl;
}

GUI::~GUI(void) {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(winren);
  SDL_Quit();
}
