#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP

#include <iostream>

namespace ayupov
{
  class StreamGuard
  {
    public:
    explicit StreamGuard(std::basic_ios< char > & stream);
    ~StreamGuard();
    private:
    std::basic_ios< char > & stream_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}

#endif
