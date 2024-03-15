#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP

#include <ios>

namespace rebdev
{
  class streamGuard
  {
    using cbios = std::basic_ios< char >;

    public:
    streamGuard(cbios& ios);
    ~streamGuard();

    private:
    cbios& ios_;
    std::streamsize precision_;
    cbios::fmtflags flags_;
  };
}

#endif
