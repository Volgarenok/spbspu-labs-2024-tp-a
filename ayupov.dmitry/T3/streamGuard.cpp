#include "streamGuard.hpp"

ayupov::StreamGuard::StreamGuard(std::basic_ios< char > & stream):
  s_(stream),
  precision_(stream.precision()),
  flags_(stream.flags())
{}

ayupov::StreamGuard::~StreamGuard()
{
  stream_.precision(precision_);
  stream_.flags(flags_);
}