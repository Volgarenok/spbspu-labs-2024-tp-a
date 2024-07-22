#ifndef IOFORMATGUARD_H
#define IOFORMATGUARD_H

#include <ios>

namespace ponamarev
{
  class ioFormatGuard
  {
  public:
    explicit ioFormatGuard(std::basic_ios < char >& s);
    ~ioFormatGuard();

  private:
    std::basic_ios < char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios < char >::fmtflags fmt_;
  };
}

#endif
