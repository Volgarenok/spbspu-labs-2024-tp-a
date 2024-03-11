#include "DataStruct.hpp"
#include "DelimiterI.hpp"
#include "StreamGuard.hpp"
#include <iostream>
#include <iomanip>
#include <bitset>

std::istream& sazanov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> sazanov::StringDelimiterI{"(:"};

  unsigned long long key1 = 0;
  char key2 = 0;
  std::string key3;
  int keyNumber = 0;
  std::bitset<3> keyNumberCounter;

  for (int i = 0; (i < 3) && (in); ++i)
  {
    in >> StringDelimiterI{"key"} >> keyNumber;
    switch (keyNumber)
    {
    case 1:
      parseKey(in, key1);
      break;
    case 2:
      parseKey(in, key2);
      break;
    case 3:
      parseKey(in, key3);
      break;
    default:
      in.setstate(std::ios::failbit);
    }
    keyNumberCounter[keyNumber % 3] = true;
  }

  in >> sazanov::DelimiterI{')'};

  if (in && keyNumberCounter.all())
  {
    value = DataStruct{key1, key2, key3};
  }
  return in;
}

void sazanov::parseKey(std::istream& in, unsigned long long& key)
{
  std::string binKey1;
  in >> DelimiterI{'0'} >> VariableDelimiterI{'b', 'B'};
  if (in)
  {
    std::getline(in, binKey1, ':');
    key = std::stoull(binKey1, nullptr, 2);
  }
}

void sazanov::parseKey(std::istream& in, char& key)
{
  in >> DelimiterI{'\''} >> key >> StringDelimiterI{"':"};
}

void sazanov::parseKey(std::istream& in, std::string& key)
{
  std::cin >> DelimiterI{'"'};
  std::getline(in, key, '"');
  std::cin >> DelimiterI{':'};
}

std::ostream& sazanov::operator<<(std::ostream& stream, const DataStruct& value)
{
  std::ostream::sentry sentry(stream);
  if (sentry) {
    StreamGuard guard(stream);
    stream << std::setprecision(1) << std::fixed
    << "(:key1 0b" << value.key1 << ":key2 '" << value.key2 << "':key3 \"" << value.key3 << "\":)";
  }
  return stream;
}

bool sazanov::DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  if (key3.size() != other.key3.size())
  {
    return key3.size() < other.key3.size();
  }
  return false;
}
