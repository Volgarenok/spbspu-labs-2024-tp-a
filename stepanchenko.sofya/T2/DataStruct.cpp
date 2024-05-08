#include "DataStruct.hpp"

std::istream& stepanchenko::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterI;
  using strDel = StringDelimiterI;
  size_t keyAmount = 3;
  in >> del{ '(' } >> del{ ':' };
  while (in && keyAmount > 0)
  {
    char num = 0;
    in >> strDel{ "key" };
    in >> num;
    switch (num)
    {
    case '1':
      in >> LongLongI{ data.key1 };
      break;
    case '2':
      in >> CharI{ data.key2 };
      break;
    case '3':
      in >> StringI{ data.key3 };
      break;
    default:
      in.setstate(std::ios::failbit);
      break;
    }
    --keyAmount;
    in >> del{ ':' };
  }
  in >> del{ ')' };

  return in;
}

std::ostream& stepanchenko::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << data.key1 << "ull"
      << ":key2 '" << data.key2
      << "':key3 \"" << data.key3 << "\":)";

  return out;
}

bool stepanchenko::operator<(const DataStruct& data1, const DataStruct& data2)
{
  if (data1.key1 != data2.key1)
  {
    return data1.key1 < data2.key1;
  }
  if (data1.key2 != data2.key2)
  {
    return data1.key2 < data2.key2;
  }
  return data1.key3.length() < data2.key3.length();
}
