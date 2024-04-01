#include "DataStruct.h"
#include <iostream>
#include "Delimiter.h"
#include "ValueI.h"
#include "StreamGuard.h"

std::istream& chernikova::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  DataStruct temp{0, 0, ""};
  std::size_t num = 0;

  in >> StringDelimiterI{"(:"};

  for (std::size_t i = 0; i < 3; ++i)
  {
    in >> StringDelimiterI{"key"} >> num;

    switch (num)
    {
    case 1:
      in >> DoubleI{temp.key1};
      break;
    case 2:
      in >> UnsignedllI{temp.key2};
      break;
    case 3:
      in >> StringI{temp.key3};
      break;
    default:
      in.setstate(std::ios::failbit);
    }
  }
  in >> DelimiterI{')'};

  if (in)
  {
    value = temp;
  }
  return in;
}

std::ostream& chernikova::operator<<(std::ostream& out, const DataStruct& 
value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);
  out << "(:key1 " << std::uppercase << std::scientific << value.key1;
  out << ":key2 " << std::oct << value.key2;
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
}

bool chernikova::operator<(const DataStruct& value1, const DataStruct& 
value2)
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
