#ifndef GUIELEM_H_
#define GUIELEM_H_

#include <memory>
#include "observer.h"
#include "subject.h"
#include "board.h"
#include "SDL.h"

class GUIElem : public Observer, Subject {
  std::shared_ptr<Board> b;
  public:
  GUIElem(std::shared_ptr<Board> b);
  virtual void handle(SDL_Renderer *r) = 0;
  ~GUIElem(void);
};

#endif
