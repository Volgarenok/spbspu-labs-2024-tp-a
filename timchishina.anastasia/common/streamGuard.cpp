#include "streamGuard.hpp"

timchishina::StreamGuard::StreamGuard(std::basic_ios< char > & s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}

timchishina::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}
