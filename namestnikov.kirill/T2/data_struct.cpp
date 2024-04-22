#include "data_struct.hpp"
#include <iomanip>
#include <string>
#include "delimeters.hpp"
#include "stream_guard.hpp"
#include "data_keys.hpp"

bool namestnikov::DataStruct::operator<(const DataStruct & data) const
{
  if (key1 == data.key1)
  {
    if (key2 == data.key2)
    {
      return key3.length() < data.key3.length();
    }
    return key2 < data.key2;
  }
  return key1 < data.key1;
}

std::istream & namestnikov::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using delC = DelimeterChar;
  using delS = DelimeterString;
  const size_t MAX_LEN_KEYS = 3;
  StreamGuard streamGuard(in);
  in >> delC{'('};
  for (size_t i = 0; i < MAX_LEN_KEYS; ++i)
  {
    size_t keyNumber = 0;
    in >> delS{":key"} >> keyNumber;
    if (keyNumber == 1)
    {
      in >> DblKey{data.key1};
    }
    else if (keyNumber == 2)
    {
      in >> OctKey{data.key2};
    }
    else if (keyNumber == 3)
    {
      in >> StrKey{data.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> delS{":)"};
  return in;
}

std::ostream & namestnikov::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  StreamGuard streamGuard(out);
  out << std::fixed << std::oct << std::setprecision(1) << "(:key1 " << data.key1 << "d";
  out << ":key2 " << "0" << data.key2;
  out << ":key3 " << "\"" << data.key3 << "\"" << ":)";
  return out;
}
