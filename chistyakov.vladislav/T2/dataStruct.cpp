#include "dataStruct.hpp"

std::istream & chistyakov::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  DataStruct dataT{0, 0, ""};
  int numOfValues = 3;
  int nowInput = 0;

  while ((!in) && (nowInput != 3))
  {
    in >> Delimiter{":key"};
    int key = 0;
    in >> key;

    if (key == 1):
    {
      in >> UllBin{dataT.key1};
      nowInput++;
    }
    else if (key == 2)
    {
      in >> RatLsp{dataT.key2};
      nowInput++;
    }
    else if (key == 3)
    {
      in >> StringT{dataT.key3};
      nowInput++;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  in >> Delimiter{":)"};
  data = dataT;
  return in;
}

std::ostream & operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << "(:key1 0b" << data.key1;
  out << ":key2 (:N" << data.key2.first << ":" << data.key2.second << ":)";
  out << ":key3 \"" << data.key3 << "\":)";

  return out;
}
