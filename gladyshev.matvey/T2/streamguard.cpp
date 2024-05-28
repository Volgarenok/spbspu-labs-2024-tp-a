#include "streamguard.hpp"

gladyshev::StreamGuard::StreamGuard(std::basic_ios< char >& s):
  s_(s),
  precision_(s.precision()),
  fmt_(s.flags())
{}

gladyshev::StreamGuard::~StreamGuard()
{
  s_.precision(precision_);
  s_.flags(fmt_);
}
