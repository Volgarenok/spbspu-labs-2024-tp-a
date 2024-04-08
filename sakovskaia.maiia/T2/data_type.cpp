#include "data_type.hpp"
#include "delimiter.hpp"
#include "stream_guard.hpp"
#include <bitset>

std::istream & sakovskaia::operator>>(std::istream & input, unsigned long long & key)
{
  std::istream::sentry guard(input);
  if(!guard)
  {
    return input;
  }
  using delimiter = delimiter_t;
  StreamGuard ios_guard(input);
  std::string binaryString;
  if ((input >> delimiter{'0'} >> delimiter{'b'}) && (input >> binaryString))
  {
    key = std::bitset<64>(binaryString).to_ullong();
    return input;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, char & key)
{
  std::istream::sentry guard(input);
  if(!guard)
  {
    return input;
  }
  using delimiter = delimiter_t;
  StreamGuard ios_guard(input);
  input >> delimiter{'\''} >> key >> delimiter{'\''};
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, std::string & key)
{
  std::istream::sentry guard(input);
  if(!guard)
  {
    return input;
  }
  using delimiter = delimiter_t;
  StreamGuard ios_guard(input);
  input >> delimiter{'"'};
  input >> key >> delimiter{'"'};
  return input;
}
