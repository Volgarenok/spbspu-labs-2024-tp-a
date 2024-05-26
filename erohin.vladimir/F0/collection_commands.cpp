#include "collection_commands.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <vector>
#include "dictionary_record.hpp"
#include "number_format.hpp"

namespace erohin
{
  struct getNumber
  {
    size_t operator()(const std::pair< std::string, size_t > & pair);
  };

  void printDictionary(const dictionary & dict, std::ostream & output, numformat_t numformat);
}

void erohin::printCommand(const collection & context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = context.at(dict_name);
  printDictionary(dict, output, numformat);
}

size_t erohin::getNumber::operator()(const std::pair< std::string, size_t > & pair)
{
  return pair.second;
}

void erohin::printDictionary(const dictionary & dict, std::ostream & output, numformat_t numformat)
{
  std::vector< size_t > number_seq;
  std::transform(dict.cbegin(), dict.cend(), std::back_inserter(number_seq), getNumber{});
  size_t total_number = std::accumulate(number_seq.cbegin(), number_seq.cend(), 0);
  using namespace std::placeholders;
  std::transform(
    dict.cbegin(),
    dict.cend(),
    std::ostream_iterator< FormattedRecord >(output, "\n"),
    std::bind(createFormattedRecord, std::bind(createRecord, _1), total_number, numformat)
  );
}
