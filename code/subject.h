#ifndef SUBJECT_H_
#define SUBJECT_H_

#include "observer.h"
#include "SDL.h"
#include <vector>
#include <memory>

class Subject {
  std::vector<std::shared_ptr<Observer>> obs;
  public:
  void add_observer(std::shared_ptr<Observer> ob);
  void remove_observer(std::shared_ptr<Observer> ob);
  void notify_observers(SDL_Renderer *r);
};

#endif
