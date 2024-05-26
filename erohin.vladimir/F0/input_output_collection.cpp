#include "input_output_collection.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <limits>
#include "dictionary_record.hpp"

namespace erohin
{
  std::pair< std::string, size_t > getRecordPair(const Record & record);
}

void erohin::inputDictionary(dictionary & dict, std::istream & input)
{
  std::transform(
    std::istream_iterator< Record >(input),
    std::istream_iterator< Record >(),
    std::inserter(dict, dict.begin()),
    getRecordPair
  );
}

void erohin::outputDictionary(const dictionary &, std::ostream &)
{
  return;
}

void erohin::inputCollection(collection & context, std::istream & input)
{
  std::string dict_name;
  while (!input.eof())
  {
    inputDictionary(context[dict_name], input);
    if (!input)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

void erohin::outputCollection(const collection &, std::ostream &)
{
  return;
}

std::pair< std::string, size_t > erohin::getRecordPair(const Record & record)
{
  return record.data;
}
