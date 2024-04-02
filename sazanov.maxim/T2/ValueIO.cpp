#include "ValueIO.hpp"
#include <iostream>
#include "DelimiterI.hpp"

std::istream& sazanov::operator>>(std::istream& in, BinUllI&& value)
{
  in >> DelimiterI< false >{'0'} >> DelimiterI< true >{'b'};
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string binKey;
  std::getline(in, binKey, ':');
  value.number = std::stoull(binKey, nullptr, 2);
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const BinUllO&& value)
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

std::istream& sazanov::operator>>(std::istream& in, CharKeyI&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> DelimiterI< false >{'\''} >> value.ch >> StringDelimiterI< false >{"':"};
  return in;
}

std::istream& sazanov::operator>>(std::istream& in, StringKeyI&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::cin >> DelimiterI< false >{'"'};
  std::getline(in, value.str, '"');
  std::cin >> DelimiterI< false >{':'};
  return in;
}
