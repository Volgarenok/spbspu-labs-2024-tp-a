#include "input_output_collection.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <limits>
#include "format.hpp"
#include "dictionary_record.hpp"
#include "dictionary.hpp"

namespace erohin
{
  std::pair< std::string, Dictionary> getNamedDictionaryPair(const NamedDictionary & dict);
}

void erohin::inputCollection(collection & dict_context, std::istream & input)
{
  while (input.good())
  {
    std::transform(
      std::istream_iterator< NamedDictionary >(input),
      std::istream_iterator< NamedDictionary >(),
      std::inserter(dict_context, dict_context.end()),
      getNamedDictionaryPair
    );
  }
}

void erohin::outputCollection(const collection & dict_context, std::ostream & output)
{
  std::transform(
    dict_context.cbegin(),
    dict_context.cend(),
    std::ostream_iterator< NamedDictionary >(output),
    createNamedDictionary
  );
}

std::pair< std::string, erohin::Dictionary> erohin::getNamedDictionaryPair(const NamedDictionary & dict)
{
  return std::make_pair(dict.dictionary.first, dict.dictionary.second);
}
