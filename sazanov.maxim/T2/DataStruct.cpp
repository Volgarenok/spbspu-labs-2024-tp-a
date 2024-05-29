#include "DataStruct.hpp"
#include <iostream>
#include <bitset>
#include <DelimiterI.hpp>
#include <StreamGuard.hpp>
#include "ValueIO.hpp"

std::istream& sazanov::operator>>(std::istream& in, DataStruct& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> StrictCaseStringDelimiterI{"(:"};

  unsigned long long key1 = 0;
  char key2 = 0;
  std::string key3;
  int keyNumber = 0;
  constexpr int TOTAL_KEYS_NUMBER = 3;
  std::bitset< TOTAL_KEYS_NUMBER > keyNumberCounter;

  for (int i = 0; (i < 3) && (in); ++i)
  {
    in >> StrictCaseStringDelimiterI{"key"} >> keyNumber;
    switch (keyNumber)
    {
    case 1:
      in >> BinUllI{key1};
      break;
    case 2:
      in >> CharKeyI{key2};
      break;
    case 3:
      in >> StringKeyI{key3};
      break;
    default:
      in.setstate(std::ios::failbit);
    }
    keyNumberCounter[keyNumber % TOTAL_KEYS_NUMBER] = true;
  }

  in >> StrictCaseDelimiterI{')'};

  if (in && keyNumberCounter.all())
  {
    value = DataStruct{key1, key2, key3};
  }
  return in;
}

std::ostream& sazanov::operator<<(std::ostream& out, const DataStruct& value)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);
  out << "(:key1 0b" << BinUllO{value.key1};
  out << ":key2 '" << value.key2 << '\'';
  out << ":key3 \"" << value.key3 << "\":)";
  return out;
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
