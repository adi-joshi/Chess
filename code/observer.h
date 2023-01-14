#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "SDL.h"

class Observer {
  public:
  virtual void update(SDL_Renderer *r) = 0;
};

#endif
