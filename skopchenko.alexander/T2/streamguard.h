#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <ios>

namespace skopchenko
{

  class StreamGuard
  {
  public:
    StreamGuard(std::basic_ios<char>& s);
    ~StreamGuard();

  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::ios::fmtflags flags_;
  };

}

#endif