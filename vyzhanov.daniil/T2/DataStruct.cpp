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
      input >> DelimeterLit{ val.key1_ };
    }
    else if (key == "key2")
    {
      input >> DelimeterOct{ val.key2_ };
    }
    else if (key == "key3")
    {
      input >> DelimeterString{ val.key3_ };
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
  output << "(:key1 " << val.key1_;
  output << ":key2 " << '0' << std::oct << val.key2_;
  output << ":key3 \"" << val.key3_ << "\":)";
  return output;
}


bool vyzhanov::operator<(const DataStruct& value1, const DataStruct& value2)
{
  if (value1.key1_ == value2.key1_)
  {
    if (value1.key2_ == value2.key2_)
    {
      return value1.key3_.size() < value2.key3_.size();
    }
    return value1.key2_ < value2.key2_;
  }
  return value1.key1_ < value2.key1_;
}
