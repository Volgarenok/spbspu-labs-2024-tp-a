#include "data_struct.hpp"
#include <iostream>
#include "format.hpp"
#include "delimiter.hpp"
#include "scope_guard.hpp"

std::istream & erohin::operator>>(std::istream & input, DataStruct & dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  DataStruct temp;
  std::string key;
  bool isKeyInput[3]{false};
  input >> Delimiter< true >{'('};
  for (int i = 0; i < 3; ++i)
  {
    input >> Delimiter< true >{':'} >> key;
    if (key == "key1")
    {
      input >> DoubleFormat{temp.key1};
      isKeyInput[0] = true;
    }
    else if (key == "key2")
    {
      input >> LongLongFormat{temp.key2};
      isKeyInput[1] = true;
    }
    else if (key == "key3")
    {
      input >> StringFormat{temp.key3};
      isKeyInput[2] = true;
    }
    else
    {
      input.setstate(std::ios::failbit);
    }
  }
  input >> Delimiter< true >{':'} >> Delimiter< true >{')'};
  const int & countUniqueKeys = isKeyInput[0] + isKeyInput[1] + isKeyInput[2];
  if (countUniqueKeys != 3)
  {
    input.setstate(std::ios::failbit);
  }
  if (input)
  {
    dest = temp;
  }
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const DataStruct & dest)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  ScopeGuard sg(output);
  output << std::fixed;
  output.precision(1);
  output << "(:key1 " << dest.key1 << 'd';
  output << ":key2 " << dest.key2 << "ll";
  output << ":key3 " << '"' << dest.key3 << '"' << ":)";
  return output;
}

bool erohin::operator<(const DataStruct & lhs, const DataStruct & rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2)
  {
    return lhs.key2 < rhs.key2;
  }
  return lhs.key3.length() < rhs.key3.length();
}
