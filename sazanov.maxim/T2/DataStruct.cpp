#include "DataStruct.hpp"
#include "DelimiterI.hpp"
#include "StreamGuard.hpp"
#include <iostream>
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
  const int TOTAL_KEYS_NUMBER = 3;
  std::bitset<TOTAL_KEYS_NUMBER> keyNumberCounter;

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
    keyNumberCounter[keyNumber % TOTAL_KEYS_NUMBER] = true;
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
    stream << "(:key1 0b" << getBinary(value.key1);
    stream << ":key2 '" << value.key2;
    stream << "':key3 \"" << value.key3 << "\":)";
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

std::string sazanov::getBinary(unsigned long long n)
{
  std::string binary;
  int counter = 0;
  int nearestDegree = 1;
  while (n != 0)
  {
    binary = (n % 2 ? "1" : "0") + binary;
    n /= 2;
    counter += 1;
    if (counter > nearestDegree || nearestDegree == 1)
    {
      nearestDegree *= 2;
    }
  }

  for (int i = 0; i != nearestDegree - counter; ++i)
  {
    binary = '0' + binary;
  }

  return binary;
}
