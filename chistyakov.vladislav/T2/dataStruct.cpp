#include "dataStruct.hpp"
#include "dataTypes.hpp"
#include "limiter.hpp"

std::istream & chistyakov::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  int nowInput = 0;
  int key = 0;
  in >> Limiter{"(:"};

  while (in && (nowInput != 3))
  {
    in >> Limiter{"key"};
    in >> key;

    if (key == 1)
    {
      in >> UllBinIO{ data.key1 };
      nowInput++;
    }
    else if (key == 2)
    {
      in >> RatLspIO{ data.key2 } >> Limiter{":"};
      nowInput++;
    }
    else if (key == 3)
    {
      in >> StringIO{ data.key3 } >> Limiter{":"};
      nowInput++;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  in >> Limiter{")"};
  return in;
}

std::ostream & chistyakov::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << "(:key1 0b" << (data.key1 == 0 ? "" : "0") << data.key1;
  out << ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 \"" << data.key3 << "\":)";

  return out;
}

bool chistyakov::DataStruct::operator<(const DataStruct & data) const
{
  if (key1 != data.key1)
  {
    return key1 < data.key1;
  }

  if (key2 != data.key2)
  {
    return key2 < data.key2;
  }

  if (key2 != data.key2)
  {
    return key2 < data.key2;
  }

  return key3.size() < data.key3.size();

}
