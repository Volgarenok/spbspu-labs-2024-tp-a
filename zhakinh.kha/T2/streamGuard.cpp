#include "streamGuard.hpp"

#include <ios>

zhakha::StreamGuard::StreamGuard(std::basic_ios< char>& s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  flags_(s.flags())
{}

zhakha::StreamGuard::~StreamGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(flags_);
}
