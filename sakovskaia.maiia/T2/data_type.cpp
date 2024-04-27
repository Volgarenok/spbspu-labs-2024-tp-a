#include "data_type.hpp"
#include "delimiter.hpp"
#include "stream_guard.hpp"
#include <bitset>
#include <iostream>

std::istream & sakovskaia::operator>>(std::istream & input, UllBin && key)
{
  std::istream::sentry guard(input);
  if(!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  std::bitset< 64 > binaryString;
  input >> Delimiter{'0'} >> Delimiter{'b'} >> binaryString;
  if (input)
  {
    key.num = binaryString.to_ullong();
  }
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, ChrLit && key)
{
  std::istream::sentry guard(input);
  if(!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  input >> Delimiter{'\''} >> key.num >> Delimiter{'\''};
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, StrKey && key)
{
  std::istream::sentry guard(input);
  if(!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  input >> Delimiter{'"'};
  std::getline(input, key.str, '"');
  return input;
}
