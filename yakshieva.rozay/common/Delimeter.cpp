#include <Delimeter.hpp>
#include <StreamGuard.hpp>

std::istream& yakshieva::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  StreamGuard streamguard(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && std::tolower(c) != dest.delimeter)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
