#include "Streamguard.hpp"

yakshieva::Streamguard::Streamguard(std::basic_ios< char >& s) :
  s_(s),
  precision_(s.precision()),
  fmt_(s.flags())
{}

yakshieva::Streamguard::~Streamguard()
{
  s_.precision(precision_);
  s_.flags(fmt_);
}
