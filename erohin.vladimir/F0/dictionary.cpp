#include "dictionary.hpp"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iterator>
#include "format.hpp"
#include "dictionary_record.hpp"

namespace erohin
{
  std::pair< std::string, size_t > getRecordPair(const Record & record);
}

std::istream & erohin::operator>>(std::istream & input, Dictionary & dict)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  Dictionary temp_dict;
  std::transform(
    std::istream_iterator< Record >(input),
    std::istream_iterator< Record >(),
    std::inserter(temp_dict.records, temp_dict.records.end()),
    getRecordPair
  );
  if (!input)
  {
    dict = std::move(temp_dict);
  }
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const Dictionary & dict)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  std::transform(
    dict.records.cbegin(),
    dict.records.cend(),
    std::ostream_iterator< Record >(output, "\n"),
    createRecord< std::string, size_t >
  );
  return output;
}

std::istream & erohin::operator>>(std::istream & input, NamedDictionary & dict)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  NamedDictionary temp_dict;
  input >> StringFormat{ temp_dict.dictionary.first, ':' };
  if (!input)
  {
    return input;
  }
  input >> temp_dict.dictionary.second;
  if (!input)
  {
    input.clear();
    dict = std::move(temp_dict);
  }
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const NamedDictionary & dict)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << ":" << dict.dictionary.first << ":\n" << dict.dictionary.second;
  return output;
}

erohin::NamedDictionary erohin::createNamedDictionary(const std::pair< std::string, Dictionary > & dict)
{
  return NamedDictionary{ dict };
}

std::pair< std::string, size_t > erohin::getRecordPair(const Record & record)
{
  return record.data;
}
