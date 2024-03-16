#include "wrappers.hpp"

std::istream& ravinskij::operator>>(std::istream& in, BinUll&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  in >> data.value;
  return in;
}

std::istream& ravinskij::operator>>(std::istream& in, HexUll&& data)
{
  std::istream::sentry guard(in);

  if (!guard)
  {
    return in;
  }

  in >> data.value;
  return in;
}

