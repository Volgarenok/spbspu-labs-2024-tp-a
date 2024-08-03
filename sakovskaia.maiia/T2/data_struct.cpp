#include "data_struct.hpp"
#include "delimiter.hpp"
#include "data_type.hpp"
#include "stream_guard.hpp"
#include <bitset>

std::istream & sakovskaia::operator>>(std::istream & input, DataStruct & data_struct)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  DataStruct data{0, 0, ""};
  int cnt = 0;
  int key_cnt = 3;
  using delimiter = Delimiter;
  input >> delimiter{'('};
  while ((input) && (cnt != key_cnt))
  {
    input >> delimiter{':'} >> delimiter{'k'} >> delimiter{'e'} >> delimiter{'y'};
    int key_num = 0;
    input >> key_num;
    if (key_num == 1)
    {
      std::cerr << "Reading key1..." << std::endl;
      input >> UllBin{data.key1};
      std::cerr << "Read key1: " << data.key1 << std::endl;
      cnt++;
    }
    else if (key_num == 2)
    {
      std::cerr << "Reading key2..." << std::endl;
      input >> ChrLit{data.key2};
      std::cerr << "Read key2: " << data.key2 << std::endl;
      cnt++;
    }
    else if (key_num == 3)
    {
      std::cerr << "Reading key3..." << std::endl;
      input >> StrKey{data.key3};
      std::cerr << "Read key3: " << data.key3 << std::endl;
      cnt++;
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
  }
  input >> delimiter{':'} >> delimiter{')'};
  if (input)
  {
    data_struct = data;
  }
  return input;
}

bool sakovskaia::operator<(const DataStruct & begin, const DataStruct & end)
{
  if (begin.key1 != end.key1)
  {
    return begin.key1 < end.key1;
  }
  if (begin.key2 != end.key2)
  {
    return begin.key2 < end.key2;
  }
  return begin.key3.size() < end.key3.size();
}

std::ostream & sakovskaia::operator<<(std::ostream & output, const DataStruct & data_struct)
{
  std::ostream::sentry guard(output);
  if (!guard)
  {
    return output;
  }
  StreamGuard s_guard(output);
  output << "(:key1 0b" << std::bitset<64>(data_struct.key1);
  output  << ":key2 \'" << data_struct.key2 << "\'";
  output  << ":key3 \"" << data_struct.key3 << "\":)";
  return output;
}
