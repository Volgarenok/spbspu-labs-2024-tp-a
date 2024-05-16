#include "DataStruct.h"

std::istream& kazennov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  using Del = Delimiter;
  using StrDel = StringDelimiter;
  in >> Del{'('};
  for (size_t i = 0; i < 3; i++)
  {
    int keyNum = 0;
    in >> StrDel{":key"} >> keyNum;
    if (keyNum == 1)
    {
      in >> Del{'\''} >> value.key1 >> Del{'\''};
    }
    if (keyNum == 2)
    {
      long long n = 0;
      unsigned long long d = 0;
      in >> StrDel{"(:N"} >> n >> StrDel{":D"} >> d >> StrDel{":)"};
      value.key2.first = n;
      value.key2.second = d;
    }
    if (keyNum == 3)
    {
      in >> Del{ '"' };
      std::getline(in, value.key3, '\"');
    }
  }
  in >> StrDel{":)"};
  return in;
}

std::ostream& kazennov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 '" << value.key1;
  out << "':key2 (:N " << value.key2.first;
  out << ":D " << value.key2.second << ":):key3 ";
  out << '"' << value.key3 << '"' << ":)";
  return out;
}

bool kazennov::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 == other.key1)
  {
    if (key2 == other.key2)
    {
      return key3.size() < other.key3.size();
    }
    return key2.first / key2.second < other.key2.first / other.key2.second;
  }
  return key1 < other.key1;
}
