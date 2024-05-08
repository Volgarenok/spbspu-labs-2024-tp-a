#include "data_keys.hpp"
#include "delimeters.hpp"
#include "stream_guard.hpp"

std::istream & namestnikov::operator>>(std::istream & in, DblKey && key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double tempKey1 = 0.0;
  using delC = DelimeterChar;
  in >> tempKey1 >> delC{'d'};
  if (in)
  {
    key.data = tempKey1;
  }
  return in;
}

std::istream & namestnikov::operator>>(std::istream & in, OctKey && key)
{
  std::istream::sentry guard(in);
  StreamGuard streamGuard(in);
  if (!guard)
  {
    return in;
  }
  unsigned long long tempKey2 = 0;
  using delC = DelimeterChar;
  in >> delC{'0'} >> std::oct >> tempKey2;
  if (in)
  {
    key.data = tempKey2;
  }
  return in;
}

std::istream & namestnikov::operator>>(std::istream & in, StrKey && key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string tempKey3 = "";
  using delC = DelimeterChar;
  in >> delC{'\"'};
  std::getline(in, tempKey3, '\"');
  if (in)
  {
    key.data = tempKey3;
  }
  return in;
}
