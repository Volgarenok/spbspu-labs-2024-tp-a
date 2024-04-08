#include "scopeGuard.hpp"

baranov::scopeGuard::scopeGuard(std::basic_ios< char > & s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precison()).
  fmt_(s.flags())
  {}

baranov::scopeGuard::~scopeGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
