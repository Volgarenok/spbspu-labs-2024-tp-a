#include "stream_guard.hpp"
#include <ios>

zaitsev::StreamGuard::StreamGuard(std::basic_ios< char >& stream):
  stream_(stream),
  flags_(stream.flags())
{}

zaitsev::StreamGuard::~StreamGuard()
{
  stream_.flags(flags_);
}
