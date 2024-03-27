#include "formats.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"

std::istream& strelyaev::operator>>(std::istream& in, Litll&& num)
{
  std::istream::sentry guard(in);
  if(!guard)
  {
    return in;
  }
  using del = delimiter_t;
  StreamGuard s_guard(in);
  in >> num.value >> del{'l'} >> del{'l'};
  return in;
}

std::istream& strelyaev::operator>>(std::istream& in, HexUll&& num)
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

std::istream& strelyaev::operator>>(std::istream& in, StringKey&& num)
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