#include "streamGuard.hpp"

demin::StreamGuard::StreamGuard(std::basic_ios< char > &s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{
}

demin::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
