#include "dataStruct.hpp"
#include "dataTypes.hpp"
#include "delimiter.hpp"

std::istream & chistyakov::operator>>(std::istream & in, DataStruct & data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  int nowInput = 0;
  int key = 0;
  in >> Delimiter{"("};

  while (in && (nowInput != 3))
  {
    in >> Delimiter{":key"};
    in >> key;

    if (key == 1)
    {
      in >> data.key1;
      nowInput++;
    }
    else if (key == 2)
    {
      in >> data.key2;
      nowInput++;
    }
    else if (key == 3)
    {
      in >> data.key3;
      nowInput++;
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }

  in >> Delimiter{":)"};
  return in;
}

std::ostream & chistyakov::operator<<(std::ostream & out, const DataStruct & data)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }

  out << "(:key1 0b" << data.key1.binaryNumber;
  out << ":key2 (:N " << data.key2.pairLlAndUll.first << ":D " << data.key2.pairLlAndUll.second << ":)";
  out << ":key3 \"" << data.key3.str << "\":)";

  return out;
}
