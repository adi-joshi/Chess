#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>

class Exception {
  std::string err;
  public:
  Exception(std::string s);
  std::string error();
  ~Exception();
};

#endif
