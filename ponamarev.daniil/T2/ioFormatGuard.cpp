#include "ioFormatGuard.h"

ponamarev::ioFormatGuard::ioFormatGuard(std::basic_ios < char >& s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

ponamarev::ioFormatGuard::~ioFormatGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
