#include "streamGuard.hpp"

belokurskaya::StreamGuard::StreamGuard(std::ios& stream):
  stream_(stream)
{
  state_ = stream_.flags();
  precision_ = stream_.precision();
  fill_ = stream_.fill();
}

belokurskaya::StreamGuard::~StreamGuard()
{
  stream_.flags(state_);
  stream_.precision(precision_);
  stream_.fill(fill_);
}
