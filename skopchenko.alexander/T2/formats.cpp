#include "formats.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& skopchenko::operator>>(std::istream& in, RatLsp&& num)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  using del = delimiter_t;
  StreamGuard s_guard(in);
  typedef std::pair<unsigned long, unsigned long> link;
  link make_my_pair(unsigned long x, unsigned long y);
  in >> del{'('} >> del{':'} >> del{'N'}  >> num.value.first >> del{':'} >> del{'D'}  >> num.value.second >> del{':'} >> del{')'};
  return in;
}

std::istream& skopchenko::operator>>(std::istream &in, SllLit&& num)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = delimiter_t;
  in >> num.value >> del{'l', false} >> del{'l', false};
  return in;
}

std::istream& skopchenko::operator>>(std::istream& in, StringKey&& num)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = delimiter_t;
  StreamGuard s_guard(in);
  in >> del{'"'};
  std::getline(in, num.str, '"');
  return in;
}

