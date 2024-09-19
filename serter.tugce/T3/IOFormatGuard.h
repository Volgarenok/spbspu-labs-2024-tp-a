#ifndef IO_FMT_GUARD_H
#define IO_FMT_GUARD_H

#include <iostream>
namespace serter
{
  class IOFormatGuard
  {
  public:
    IOFormatGuard(std::basic_ios< char >& stream);
    ~IOFormatGuard();
  private:
    std::basic_ios< char >& referenceToStream_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags formatFlags_;
  };
}
#endif

