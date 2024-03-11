#include "formatGuard.hpp"

novikov::FormatGuard::FormatGuard(std::basic_ios< char >& stream):
  stream_(stream),
  flags_(stream.flags())
{}

novikov::FormatGuard::~FormatGuard()
{
  stream_.flags(flags_);
}
