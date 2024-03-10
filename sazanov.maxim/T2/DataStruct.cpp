#include "DataStruct.hpp"
#include "DelimiterI.hpp"
#include <iostream>

std::istream& sazanov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> sazanov::DelimiterI{'('};

  unsigned long long key1 = 0;
  char key2 = 0;
  std::string key3;
  int keyNumber = 0;
  int keyNumberHistory[] {0, 0, 0};

  for (int i = 0; (i < 3) && (in); ++i)
  {
    in >> StringDelimiterI{":key"};
    in >> keyNumber;
    switch (keyNumber)
    {
    case 1:
      in >> key1;
      break;
    case 2:
      in >> DelimiterI{'\''} >> key2 >> DelimiterI{'\''};
      break;
    case 3:
      std::cin >> DelimiterI{'"'};
      std::getline(in, key3, '"');
      break;
    default:
      in.setstate(std::ios::failbit);
    }

    keyNumberHistory[(keyNumber - 1) % 3] = 1;
  }

  if (in && keyNumberHistory[0] && keyNumberHistory[1] && keyNumberHistory[2])
  {
    value = sazanov::DataStruct(key1, key2, key3);
  }
  return in;
}
