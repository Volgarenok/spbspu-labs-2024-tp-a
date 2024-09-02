#include "formatGuard.hpp"

novikov::FormatGuard::FormatGuard(std::basic_ios< char >& stream):
  stream_(stream),
  flags_(stream.flags()),
  precision_(stream.precision())
{}

novikov::FormatGuard::~FormatGuard()
{
  stream_.flags(flags_);
  stream_.precision(precision_);
}
