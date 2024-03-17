#include "ValueO.hpp"
#include <ostream>

std::ostream& sazanov::operator<<(std::ostream& out, const BinUllValueO& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  const int NUMBER_OF_BITS = getNumberOfBits(value.number);
  for (int bitNumber = 1; bitNumber <= NUMBER_OF_BITS; ++bitNumber)
  {
    out << (value.number >> (NUMBER_OF_BITS - bitNumber)) % 2;
  }
  return out;
}

int sazanov::getNumberOfBits(unsigned long long int value)
{
  int num = 0;
  while (value > 0)
  {
    value /= 2;
    ++num;
  }
  if (num == 0)
  {
    ++num;
  }
  return num;
}
