include "FormatGuard.hpp"

#include <iostream>

serter::FormatGuard::FormatGuard(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  flags_(s.flags())
{}

serter::FormatGuard::~FormatGuard()
{
  s_.precision(precision_);
  s_.flags(flags_);
}

