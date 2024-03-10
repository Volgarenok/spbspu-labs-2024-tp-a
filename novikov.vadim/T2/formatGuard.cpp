#include "formatGuard.hpp"

novikov::FormatGuard::FormatGuard(std::basic_ios< char >& stream):
  stream_(stream),
  flags_(stream.flags()),
  precision_(stream.precision())
{}

novikov::FormatGuard::~FormatGuard()
{
  stream_.precision(precision_);
  stream_.flags(flags_);
}