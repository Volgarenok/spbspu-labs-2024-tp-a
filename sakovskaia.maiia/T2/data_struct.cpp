#include "data_struct.hpp"
#include "delimiter.hpp"

std::istream & sakovskaia::operator>>(std::istream & input, DataStruct & data_struct)
{
  std::istream::sentry guard(input);
  int cnt = 0;
  int key_cnt = 3;
  using delimiter = delimiter_t;
  input >> delimiter{'('};
  while ((input) && (cnt != key_cnt))
  {
    input >> delimiter{':'} >> delimiter{'k'} >> delimiter{'e'} >> delimiter{'y'};
  }
  input >> delimiter{':'} >> delimiter{')'};
  return input;
}
