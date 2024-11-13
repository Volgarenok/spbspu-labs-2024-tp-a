#include "StreamGuard.h"

stepanov::StreamGuard::StreamGuard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  fmt_(s.flags())
{}

stepanov::StreamGuard::~StreamGuard()
{
  s_.fill(fill_);
  s_.flags(fmt_);
}

