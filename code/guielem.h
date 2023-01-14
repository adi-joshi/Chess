#ifndef GUIELEM_H_
#define GUIELEM_H_

#include "observer.h"
#include "subject.h"
#include "board.h"
#include <memory>

class GUIElem : public Observer, Subject {
  int w;
  int h;
  std::shared_ptr<Board> b;
  public:
  GUIElem(int w, int h, Board *b);
  virtual void handle(void);
  ~GUIElem(void);
};

#endif
