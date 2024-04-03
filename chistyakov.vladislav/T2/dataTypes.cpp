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

  in >> Delimiter{"0"} >> Delimiter{"b"} >> binNum.binaryNumber;
  return in;
}


std::istream & chistyakov::operator>>(std::istream & in, RatLsp & pair)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Delimiter{"(:N"} >> pair.pairLlAndUll.first >> Delimiter{":"} >> pair.pairLlAndUll.second >> Delimiter{":):"};
  return in;
}
