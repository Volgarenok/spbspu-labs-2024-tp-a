#include "StreamGuard.h"

namespace stepanov
{
  StreamGuard::StreamGuard(std::basic_ios< char >& s):
    s_(s),
    fill_(s.fill()),
    fmt_(s.flags())
  {}

  StreamGuard::~StreamGuard()
  {
    s_.fill(fill_);
    s_.flags(fmt_);
  }
}

