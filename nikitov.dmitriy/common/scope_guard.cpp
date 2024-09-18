#include "scope_guard.hpp"
#include <ios>

nikitov::ScopeGuard::ScopeGuard(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}

nikitov::ScopeGuard::~ScopeGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
