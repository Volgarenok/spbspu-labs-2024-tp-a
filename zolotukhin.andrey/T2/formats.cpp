#include "formats.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& zolotukhin::operator>>(std::istream& in, RatLsp&& num)
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

std::istream& zolotukhin::operator>>(std::istream& in, HexUll&& num)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = delimiter_t;
  StreamGuard s_guard(in);
  in >> std::hex;
  in >> del{'0'} >> del{'x'} >> num.value;
  return in;
}

std::istream& zolotukhin::operator>>(std::istream& in, StringKey&& num)
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
