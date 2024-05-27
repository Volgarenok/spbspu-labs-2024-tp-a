#include "input_output_collection.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <limits>
#include "format.hpp"
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
    std::inserter(dict, dict.end()),
    getRecordPair
  );
}

void erohin::outputDictionary(const dictionary & dict, std::ostream & output)
{
  std::transform(
    dict.cbegin(),
    dict.cend(),
    std::ostream_iterator< Record >(output, "\n"),
    createRecord< std::string, size_t >
  );
}

void erohin::inputCollection(collection & dict_context, std::istream & input)
{
  std::string dict_name;
  input >> StringFormat{ dict_name, ':' };
  while (!input.eof())
  {
    inputDictionary(dict_context[dict_name], input);
    if (!input)
    {
      input.clear();
    }
    input >> StringFormat{ dict_name, ':' };
  }
}

void erohin::outputCollection(const collection & dict_context, std::ostream & output)
{
  auto begin = dict_context.cbegin();
  auto end = dict_context.cend();
  while (begin != end)
  {
    output << ":" << begin->first << ":" << "\n";
    outputDictionary(begin->second, output);
    ++begin;
  }
}

std::pair< std::string, size_t > erohin::getRecordPair(const Record & record)
{
  return record.data;
}
