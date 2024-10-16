#include "data_struct.hpp"
#include "data_type.hpp"
#include <stream_guard.hpp>
#include <delimiter.hpp>

std::istream & sakovskaia::operator>>(std::istream & input, DataStruct & data_struct)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  StreamGuard ios_guard(input);
  DataStruct data{0, 0, ""};
  size_t cnt = 0;
  size_t key_cnt = 3;
  using delimiter = Delimiter;
  input >> delimiter{"("};
  while ((input) && (cnt != key_cnt))
  {
    input >> delimiter{":key"};
    int key_num = 0;
    input >> key_num;
    if (key_num == 1)
    {
      input >> UllBin{data.key1};
      cnt++;
    }
    else if (key_num == 2)
    {
      input >> ChrLit{data.key2};
      cnt++;
    }
    else if (key_num == 3)
    {
      input >> StrKey{data.key3};
      cnt++;
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
  }
  input >> delimiter{":)"};
  data_struct = data;
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
  output << "(:key1 0b" << (data_struct.key1 == 0 ? "" : "0") << data_struct.key1;
  output  << ":key2 \'" << data_struct.key2 << "\'";
  output  << ":key3 \"" << data_struct.key3 << "\":)";
  return output;
}
