#include "data_type.hpp"
#include "delimiter.hpp"
#include "stream_guard.hpp"
#include <bitset>
#include <iostream>

std::istream & sakovskaia::operator>>(std::istream & input, UllBin && key)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  input >> Delimiter{'0'} >> Delimiter{'b'} >> key.num;
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, ChrLit && key)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  char chr;
  input >> Delimiter{'\''} >> chr >> Delimiter{'\''};
  if (input)
  {
    key.chr_lit = chr;
  }
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, StrKey && key)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  input >> Delimiter{'"'};
  std::getline(input, key.str, '"');
  return input;
}
