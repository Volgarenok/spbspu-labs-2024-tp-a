#include "inguard.hpp"

vojuck::InGuard::InGuard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  precisiom_(s.precision()),
  fmt_(s.flags())
  {}

vojuck::InGuard::~InGuard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}
