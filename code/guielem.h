#ifndef GUIELEM_H_
#define GUIELEM_H_

#include <memory>
#include "observer.h"
#include "subject.h"
#include "board.h"
#include "SDL.h"

class GUIElem : public Observer, public Subject {
  protected:
  // the window area on which to display is determined by the renderer.
  std::shared_ptr<Board> b;
  SDL_Rect *viewport;
  public:
  GUIElem(std::shared_ptr<Board> b);
  virtual void load_assets(SDL_Renderer *r) = 0;
  virtual void handle(SDL_Renderer *r) = 0;
  // copies this->viewport and then returns it.
  SDL_Rect get_viewport(void);

  // changes values of this->viewport to vp
  virtual void set_viewport(SDL_Rect *vp);
  ~GUIElem(void);
};

#endif
