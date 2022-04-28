#include "subject.h"

Subject::Subject(void) {}

void Subject::attach(Observer *o) {
  ob.push_back(o);
}

const std::vector<Observer *> Subject::get_observers(void) {
  return ob;
}

Subject::~Subject(void) {}
