#include "dataTypes.hpp"
#include <iostream>
#include "limiter.hpp"

std::istream & chistyakov::operator>>(std::istream & in, UllBinIO && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Limiter{"0b"} >> data.value;
  return in;
}


std::istream & chistyakov::operator>>(std::istream & in, RatLspIO && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Limiter{"(:N"} >> data.value.first >> Limiter{":D"} >> data.value.second >> Limiter{":)"};

  return in;
}

std::istream & chistyakov::operator>>(std::istream & in, StringIO && data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> Limiter{"\""};
  std::getline(in, data.value, '\"');
  return in;
}
