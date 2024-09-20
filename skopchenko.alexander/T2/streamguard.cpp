#include "streamguard.h"

namespace skopchenko
{

  StreamGuard::StreamGuard(std::basic_ios<char> &s) :
    s_(s), precision_(s.precision()), flags_(s.flags())
  {
  }

  StreamGuard::~StreamGuard()
  {
    s_.precision(precision_);
    s_.flags(flags_);
  }

}
