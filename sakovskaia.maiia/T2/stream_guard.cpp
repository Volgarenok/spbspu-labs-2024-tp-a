#include "stream_guard.hpp"

sakovskaia::StreamGuard::StreamGuard(std::basic_ios< char > & ios):
  ios_(ios),
  precision_(ios.precision()),
  flags_(ios.flags())
{}

sakovskaia::StreamGuard::~StreamGuard()
{
  ios_.precision(precision_);
  ios_.flags(flags_);
}
