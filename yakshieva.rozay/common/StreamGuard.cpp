#include <StreamGuard.hpp>

yakshieva::StreamGuard::StreamGuard(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  fmt_(s.flags())
{}

yakshieva::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(fmt_);
}
