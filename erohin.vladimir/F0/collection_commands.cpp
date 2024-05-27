#include "collection_commands.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <vector>
#include "dictionary_record.hpp"
#include "number_format.hpp"

void erohin::addTextCommand(texts_source & context, std::istream & input, std::ostream &)
{
  std::string text_name, text_source;
  input >> text_name >> text_source;
  auto iter_pair = context.insert(std::make_pair(text_name, text_source));
  if (!iter_pair.second)
  {
    throw std::logic_error("addtext: bad insertion into texts source");
  }
}

namespace erohin
{
  void createDictionary(dictionary & dict, const std::string & file_name);
}

void erohin::createDictCommand(collection & dict_context, const texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string dict_name, text_name;
  input >> dict_name >> text_name;
  dictionary temp_dict;
  createDictionary(temp_dict, text_context.at(text_name));
  auto iter_pair = dict_context.insert(std::make_pair(dict_name, std::move(temp_dict)));
  if (!iter_pair.second)
  {
    throw std::logic_error("createdict: bad insertion into collection");
  }
}

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

void erohin::createDictionary(dictionary & dict, const std::string & file_name)
{
  std::fstream file;
  file.open(file_name);
  if (!file)
  {
    throw std::runtime_error("File reading error");
  }
  std::string word;
  dictionary temp_dict;
  while (file >> word)
  {
    ++temp_dict[word];
  }
  dict = std::move(temp_dict);
  file.close();
}
