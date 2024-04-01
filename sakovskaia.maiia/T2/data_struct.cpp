#include "data_struct.hpp"
#include "delimiter.hpp"
#include "data_type.hpp"

std::istream & sakovskaia::operator>>(std::istream & input, DataStruct & data_struct)
{
  std::istream::sentry guard(input);
  StreamGuard ios_guard(input);
  DataStruct data{0, 0, ""};
  int cnt = 0;
  int key_cnt = 3;
  using delimiter = delimiter_t;
  input >> delimiter{'('};
  while ((input) && (cnt != key_cnt))
  {
    input >> delimiter{':'} >> delimiter{'k'} >> delimiter{'e'} >> delimiter{'y'};
    int key_num = 0;
    input >> key_num;
    if (key_num == 1)
    {
      input >> sakovskaia::operator>>(std::istream & input, data.key1);
      cnt++;
    }
    else if (key_num == 2)
    {
      input >> sakovskaia::operator>>(std::istream & input, data.key2);
      cnt++;
    }
    else if (key_num == 3)
    {
      input >> sakovskaia::operator>>(std::istream & input, data.key3);
      cnt++;
    }
  }
  input >> delimiter{':'} >> delimiter{')'};
  data_struct = data;
  return input;
}
