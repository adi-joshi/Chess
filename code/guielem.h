#ifndef GUIELEM_H_
#define GUIELEM_H_

#include <memory>
#include "observer.h"
#include "subject.h"
#include "board.h"
#include "SDL.h"

class GUIElem : public Observer, public Subject {
  protected:
  int win_w;
  int win_h;
  std::shared_ptr<Board> b;
  public:
  GUIElem(int win_w, int win_h, std::shared_ptr<Board> b);
  virtual void load_assets(SDL_Renderer *r) = 0;
  virtual void handle(SDL_Renderer *r) = 0;
  ~GUIElem(void);
};

#endif
