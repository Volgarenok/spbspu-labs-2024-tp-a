#include "DataStruct.hpp"
#include <iomanip>
#include "delimeter.hpp"
#include "StreamGuard.hpp"

std::istream& vyzhanov::operator>>(std::istream& input, DataStruct& val)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  StreamGuard streamGuard(input);
  input >> Delimeter{ '(' } >> Delimeter{ ':' };
  for (size_t i = 0; i < 3; ++i)
  {
    std::string key = "";
    input >> key;
    if (key == "key1")
    {
      input >> DelimeterLit{ val.key1 };
    }
    else if (key == "key2")
    {
      input >> DelimeterOct{ val.key2 };
    }
    else if (key == "key3")
    {
      input >> DelimeterString{ val.key3 };
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
    input >> Delimeter{ ':' };
  }
  input >> Delimeter{ ')' };
  return input;
}

std::ostream& vyzhanov::operator<<(std::ostream& output, const DataStruct& val)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  StreamGuard streamGuard(output);
  output << "(:key1 " << val.key1 << "ull";
  output << ":key2 " << '0' << std::oct << val.key2;
  output << ":key3 \"" << val.key3 << "\":)";
  return output;
}


bool vyzhanov::operator<(const DataStruct& value1, const DataStruct& value2)
{
  if (value1.key1 == value2.key1)
  {
    if (value1.key2 == value2.key2)
    {
      return value1.key3.size() < value2.key3.size();
    }
    return value1.key2 < value2.key2;
  }
  return value1.key1 < value2.key1;
}
