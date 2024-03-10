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

  in >> sazanov::StringDelimiterI{"(:"};

  unsigned long long int key1 = 0;
  std::string binKey1;
  char key2 = 0;
  std::string key3;
  int keyNumber = 0;
  int keyNumberHistory[] {0, 0, 0};

  for (int i = 0; (i < 3) && (in); ++i)
  {
    in >> StringDelimiterI{"key"} >> keyNumber;
    switch (keyNumber)
    {
    case 1:
      in >> DelimiterI{'0'} >> VariableDelimiterI{'b', 'B'};
      std::getline(in, binKey1, ':');
      key1 = std::stoull(binKey1, nullptr, 2);
      break;
    case 2:
      in >> DelimiterI{'\''} >> key2 >> StringDelimiterI{"':"};
      break;
    case 3:
      std::cin >> DelimiterI{'"'};
      std::getline(in, key3, '"');
      std::cin >> DelimiterI{':'};
      break;
    default:
      in.setstate(std::ios::failbit);
    }
    keyNumberHistory[(keyNumber - 1) % 3] = 1;
  }

  in >> sazanov::DelimiterI{')'};

  if (in && keyNumberHistory[0] && keyNumberHistory[1] && keyNumberHistory[2])
  {
    value = sazanov::DataStruct(key1, key2, key3);
  }
  return in;
}
