#include "DataStruct.h"
#include "Keys.h"

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
      in >> CharKey{ value.key1 };
    }
    if (keyNum == 2)
    {
      in >> RatKey{ value.key2 };
    }
    if (keyNum == 3)
    {
      in >> StrKey{ value.key3 };
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
