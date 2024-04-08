#include "scopeGuard.hpp"

zakozhurnikova::ScopeGuard::ScopeGuard(std::basic_ios< char >&stream):
  stream_(stream),
  flags_(stream.flags()),
  precision_(stream.precision())
{}

zakozhurnikova::ScopeGuard::~ScopeGuard()
{
  stream_.precision(precision_);
  stream_.flags(flags_);
}
