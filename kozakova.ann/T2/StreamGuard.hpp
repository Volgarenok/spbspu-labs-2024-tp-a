#pragma once
#ifndef STREAMGUARD
#define STREAMGUARD

#include <ios>

namespace kozakova {
  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios<char>& s);
    ~StreamGuard();
  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
  };
}
#endif //!STREAMGUARD