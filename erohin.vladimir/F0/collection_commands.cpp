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

  std::pair< std::string, size_t > inputPair(std::istream & input);
}

void erohin::printCommand(const collection & context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = context.at(dict_name);
  if (dict.empty())
  {
    return;
  }
  std::vector< size_t > number_seq;
  std::transform(dict.cbegin(), dict.cend(), std::back_inserter(number_seq), getNumber{});
  size_t total_number = std::accumulate(number_seq.cbegin(), number_seq.cend(), 0);
  std::transform(
    dict.cbegin(),
    dict.cend(),
    std::ostream_iterator< Record >(output, "\n"),
    std::bind(convertToRecord, std::placeholders::_1, total_number, numformat)
  );
}

size_t erohin::getNumber::operator()(const std::pair< std::string, size_t > & pair)
{
  return pair.second;
}

std::pair< std::string, size_t > erohin::inputPair(std::istream & input)
{
  std::string word;
  size_t number = 0;
  input >> word >> number;
  return std::make_pair(word, number);
}
