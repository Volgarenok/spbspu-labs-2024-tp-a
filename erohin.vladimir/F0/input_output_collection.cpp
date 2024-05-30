#include "input_output_collection.hpp"
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <limits>
#include "format.hpp"
#include "dictionary_record.hpp"
#include "dictionary.hpp"

void erohin::inputCollection(collection & dict_context, std::istream & input)
{
  while (!input.eof())
  {
    std::string dict_name;
    input >> dict_name;
    Dictionary & dict = dict_context[dict_name];
    std::copy(
      std::istream_iterator< Dictionary >(input),
      std::istream_iterator< Dictionary >(),
      std::inserter(dict, dict.end())
    );
    if (input.fail())
    {
      input.clear();
    }
  }

}

void erohin::outputCollection(const collection & dict_context, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  Dictionary & dict = dict_context[dict_name];
  std::copy(
    std::istream_iterator< Dictionary >(input),
    std::istream_iterator< Dictionary >(),
    std::inserter(dict, dict.end())
  );

  std::transform(
    dict.records.cbegin(),
    dict.records.cend(),
    std::ostream_iterator< Record >(output, "\n"),
    createRecord< std::string, size_t >
  );
  return output;
}
