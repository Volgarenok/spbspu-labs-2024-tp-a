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
  using delimiter = Delimiter;
  StreamGuard ios_guard(input);
  std::string binaryString;
  if ((input >> delimiter{'0'} >> delimiter{'b'}) && (input >> binaryString))
  {
    key.num = std::bitset<64>(binaryString).to_ullong();
    return input;
  }
  else
  {
    input.setstate(std::ios::failbit);
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
