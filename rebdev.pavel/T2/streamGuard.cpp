#include "streamGuard.hpp"

rebdev::streamGuard::streamGuard(cbios& ios):
  ios_(ios),
  precision_(ios.precision()),
  flags_(ios.flags())
{}

rebdev::streamGuard::~streamGuard()
{
  ios_.precision(precision_);
  ios_.flags(flags_);
}
