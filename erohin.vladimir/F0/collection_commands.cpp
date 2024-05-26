#include "collection_commands.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <vector>
#include "number_format.hpp"

/*
std::ostream & erohin::print(std::ostream & output, const std::pair< std::string, size_t > & pair)
{
  return output << pair.first << " " << pair.second;
}
*/

erohin::Record erohin::convertToRecord(const std::pair< std::string, size_t > & pair, size_t total_number, numformat_t numformat)
{
  return std::move(Record{ pair.first, pair.second, total_number, numformat });
}

std::ostream & erohin::operator<<(std::ostream & output, const Record & record)
{
  return output << record.word << ": " << NumberFormat{ record.number, record.total_number, record.numformat };
}

namespace erohin
{
  struct getNumber
  {
    size_t operator()(const std::pair< std::string, size_t > & pair)
    {
      return pair.second;
    }
  };
}

void erohin::print_command(const collection & context, std::istream & input, std::ostream & output, numformat_t numformat)
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
