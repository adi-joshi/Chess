#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <vector>
#include "observer.h"

class Subject {
  protected:
  std::vector<Observer *> ob;
  public:
  Subject();
  void attach(Observer *ob);
  const std::vector<Observer *> get_observers();
  ~Subject();
};

#endif
