#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP

#include <iostream>

namespace yakshieva
{
  class Streamguard {
  public:
    explicit Streamguard(std::basic_ios< char >& s);
    ~Streamguard();
  private:
    std::basic_ios< char >& s_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
