#include "exception.h"

Exception::Exception(std::string s)
  : err{s}
{}

std::string Exception::error(void) {
  return err;
}

Exception::~Exception(void) {}
