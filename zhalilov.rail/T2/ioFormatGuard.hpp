#ifndef IOFORMATGUARD_HPP
#define IOFORMATGUARD_HPP

#include <ios>

namespace zhalilov
{
  class ioFormatGuard
  {
  public:
    explicit ioFormatGuard(std::basic_ios < char > &s);
    ~ioFormatGuard();

  private:
    std::basic_ios < char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios < char >::fmtflags fmt_;
  };
}

#endif
