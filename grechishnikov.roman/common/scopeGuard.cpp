#include "scopeGuard.hpp"

grechishnikov::ScopeGuard::ScopeGuard(std::basic_ios< char >& stream):
  stream_(stream),
  flags_(stream.flags()),
  precision_(stream.precision())
{}

grechishnikov::ScopeGuard::~ScopeGuard()
{
  stream_.flags(flags_);
  stream_.precision(precision_);
}
