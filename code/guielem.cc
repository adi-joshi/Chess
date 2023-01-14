#include "guielem.h"

GUIElem::GUIElem(int win_w, int win_h, std::shared_ptr<Board> b)
  : win_w{win_w}, win_h{win_h}, b{b}
{}

GUIElem::~GUIElem(void) {}
