#include <scopeGuard.hpp>

basko::ScopeGuard::ScopeGuard(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}

basko::ScopeGuard::~ScopeGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
