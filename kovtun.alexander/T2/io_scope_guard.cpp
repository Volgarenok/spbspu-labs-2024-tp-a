#include "io_scope_guard.hpp"


kovtun::IOScopeGuard::IOScopeGuard(std::basic_ios< char > & s) :
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  flags_(s.flags())
{}

kovtun::IOScopeGuard::~IOScopeGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(flags_);
}
