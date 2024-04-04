#include "dataTypes.hpp"
#include <iostream>
#include "delimiter.hpp"

std::istream & chistyakov::operator>>(std::istream & in, UllBin & binNum)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{"0b"} >> binNum.binaryNumber;
  return in;
}


std::istream & chistyakov::operator>>(std::istream & in, RatLsp & pair)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{"(:N"} >> pair.pairLlAndUll.first >> Delimiter{":D"} >> pair.pairLlAndUll.second >> Delimiter{":)"};

  return in;
}

std::istream & chistyakov::operator>>(std::istream & in, StringT & str)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{"\""};
  std::getline(in, str.str, '\"');
  return in;
}
