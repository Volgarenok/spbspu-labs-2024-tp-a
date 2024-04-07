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
      in >> LongLongI{ data.key1_ };
      break;
    case '2':
      in >> CharI{ data.key2_ };
      break;
    case '3':
      in >> StringI{ data.key3_ };
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
  out << "(:key1 " << data.key1_ << "ull" 
      << ":key2 '" << data.key2_
      << "':key3 " << data.key3_ << ":)";

  return out;
}

bool stepanchenko::operator<(const DataStruct& data1, const DataStruct& data2)
{
  if (data1.key1_ == data2.key2_)
  {
    if (data1.key2_ == data2.key2_)
    {
      return data1.key3_.length() < data2.key3_.length();
    }
    return data1.key2_ < data2.key2_;
  }
  return data1.key1_ < data2.key1_;
}
