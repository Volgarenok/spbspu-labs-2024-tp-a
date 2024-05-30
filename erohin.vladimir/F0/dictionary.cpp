#include "dictionary.hpp"
#include <iostream>
#include <string>
#include <map>
#include "dictionary_record.hpp"

std::istream & erohin::operator>>(std::istream & input, Dictionary & dict)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  Dictionary temp_dict;
  Record record;
  input >> record;
  while (input.good())
  {
    temp_dict.records.insert(record.data);
    input >> record;
  }
  dict = std::move(temp_dict);
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const Dictionary & dict)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  auto begin = dict.records.cbegin();
  auto end = dict.records.cend();
  while (begin != end)
  {
    output << Record(*(begin++)) << "\n";
  }
  return output;
}
