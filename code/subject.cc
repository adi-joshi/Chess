#include "subject.h"

void Subject::add_observer(std::shared_ptr<Observer> ob) {
  obs.push_back(ob);
}

void Subject::remove_observer(std::shared_ptr<Observer> ob) {
  for (int i = 0; i < obs.size(); i++) {
    if (obs[i] == ob) {
      obs.erase(obs.begin() + i);
      return;
    }
  }
}

void Subject::notify_observers(void) {
  for (auto o : obs) {
    o->update();
  }
}
