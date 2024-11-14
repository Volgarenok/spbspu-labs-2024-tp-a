#include "streamguard.hpp"

prisyach::StreamGuard::StreamGuard(std::basic_ios< char > & s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}

prisyach::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
