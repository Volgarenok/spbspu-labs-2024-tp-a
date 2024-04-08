#include "data_type.hpp"
#include "delimiter.hpp"
#include "stream_guard.hpp"
#include <bitset>

std::istream & sakovskaia::operator>>(std::istream & input, unsigned long long & key)
{
  std::istream::sentry guard(input);
  using delimiter = delimiter_t;
  StreamGuard ios_guard(input);
  input  >> delimiter{'0'} >> delimiter{'b'} >> std::bitset<64>(key);
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, char & key)
{
  std::istream::sentry guard(input);
  using delimiter = delimiter_t;
  StreamGuard ios_guard(input);
  input >> delimiter{'\''} >> key >> delimiter{'\''};
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, std::string & key)
{
  std::istream::sentry guard(input);
  using delimiter = delimiter_t;
  StreamGuard ios_guard(input);
  input >> delimiter{'"'};
  input >> key >> delimiter{'"'};
  return input;
}
