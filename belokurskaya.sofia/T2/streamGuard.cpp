#include "streamGuard.hpp"


StreamGuard::StreamGuard(std::ios& stream):
  stream_(stream)
{
  state_ = stream_.flags();
  precision_ = stream_.precision();
  fill_ = stream_.fill();
}

StreamGuard::~StreamGuard()
{
  stream_.flags(state_);
  stream_.precision(precision_);
  stream_.fill(fill_);
}