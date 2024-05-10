#include "scope_guard.hpp"

erohin::ScopeGuard::ScopeGuard(std::basic_ios< char > & stream):
  stream_(stream),
  fill_(stream.fill()),
  precision_(stream.precision()),
  flags_(stream.flags())
{}

erohin::ScopeGuard::~ScopeGuard()
{
  stream_.fill(fill_);
  stream_.precision(precision_);
  stream_.flags(flags_);
}
