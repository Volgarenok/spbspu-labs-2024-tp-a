#include "collection_commands.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>
#include <forward_list>
#include "dictionary_record.hpp"
#include "number_format.hpp"

void erohin::addTextCommand(texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string text_name, text_source;
  input >> text_name >> text_source;
  auto iter_pair = text_context.insert(std::make_pair(text_name, text_source));
  if (!iter_pair.second)
  {
    throw std::logic_error("addtext: bad insertion into texts source");
  }
}

void erohin::removeTextCommand(texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string text_name;
  input >> text_name;
  auto removed_num = text_context.erase(text_name);
  if (!removed_num)
  {
    throw std::logic_error("removetext: bad removal from texts source");
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
    throw std::logic_error("createdict: bad insertion into dictionary collection");
  }
}

void erohin::removeDictCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name;
  input >> dict_name;
  auto removed_num = dict_context.erase(dict_name);
  if (!removed_num)
  {
    throw std::logic_error("removetext: bad removal from dictionary collection");
  }
}

namespace erohin
{
  void printDictionary(const dictionary & dict, std::ostream & output, numformat_t numformat);
}

void erohin::printCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = dict_context.at(dict_name);
  printDictionary(dict, output, numformat);
}

void erohin::countCommand(const collection & dict_context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = dict_context.at(dict_name);
  size_t total_number = detail::countTotalNumber(dict);
  size_t unique_number = dict.size();
  output << "words: " << total_number << "; unique words: " << unique_number << "\n";
}

namespace erohin
{
  using sorted_dictionary = std::multimap< size_t, std::string >;
  void createSortedDictionary(sorted_dictionary & sorted_dict, const dictionary & source);
  void printSortedDictionary(const sorted_dictionary & sorted_dict, std::ostream & output, numformat_t numformat);
}

void erohin::sortCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = dict_context.at(dict_name);
  std::multimap< size_t, std::string > sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  printSortedDictionary(sorted_dict, output, numformat);
}

void erohin::findCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name, word;
  input >> dict_name >> word;
  const dictionary & dict = dict_context.at(dict_name);
  auto found_iter = dict.find(word);
  if (found_iter != dict.end())
  {
    size_t total_number = detail::countTotalNumber(dict);
    output << createFormattedRecord(Record(*found_iter), total_number, numformat) << "\n";
  }
  else
  {
    throw std::logic_error("find: cannot find word");
  }
}

namespace erohin
{
  bool isNewDictionary(const collection & dict_context, const std::string & new_dict_name);
}

void erohin::topCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string new_dict_name, dict_name;
  size_t num = 0;
  input >> new_dict_name >> dict_name >> num;
  if (!input || !isNewDictionary(dict_context, new_dict_name))
  {
    throw std::logic_error("top: wrong argument input");
  }
  const dictionary & dict = dict_context.at(dict_name);
  std::multimap< size_t, std::string > sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  dictionary new_dict;
  detail::insertNumRecords(new_dict, num, sorted_dict.crbegin(), sorted_dict.crend());
  dict_context[new_dict_name] = std::move(new_dict);
}

void erohin::bottomCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string new_dict_name, dict_name;
  size_t num;
  input >> new_dict_name >> dict_name >> num;
  if (!input || !isNewDictionary(dict_context, new_dict_name))
  {
    throw std::logic_error("bottom: wrong argument input");
  }
  const dictionary & dict = dict_context.at(dict_name);
  std::multimap< size_t, std::string > sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  dictionary new_dict;
  detail::insertNumRecords(new_dict, num, sorted_dict.cbegin(), sorted_dict.cend());
  dict_context[new_dict_name] = std::move(new_dict);
}

namespace erohin
{
  bool hasDifference(const record_pair & pair, const dictionary & dict);
  record_pair makeDifference(const record_pair & pair, const dictionary & dict);
}

void erohin::differCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string new_dict_name, first_dict_name, second_dict_name;
  input >> new_dict_name >> first_dict_name >> second_dict_name;
  if (!isNewDictionary(dict_context, new_dict_name))
  {
    throw std::logic_error("differ: dictionary has already existed");
  }
  const dictionary & first_dict = dict_context.at(first_dict_name);
  const dictionary & second_dict = dict_context.at(second_dict_name);
  dictionary temp_dict;
  using namespace std::placeholders;
  copy_if(
    first_dict.cbegin(),
    first_dict.cend(),
    std::inserter(temp_dict, temp_dict.end()),
    std::bind(hasDifference, _1, std::cref(second_dict))
  );
  dictionary new_dict;
  transform(
    temp_dict.cbegin(),
    temp_dict.cend(),
    std::inserter(new_dict, new_dict.end()),
    std::bind(makeDifference, _1, std::cref(second_dict))
  );
  if (new_dict.empty())
  {
    throw std::underflow_error("differ: Empty difference of two dictionaries");
  }
  dict_context[new_dict_name] = std::move(new_dict);
}

namespace erohin
{
  using dict_pair = std::pair< dictionary, dictionary >;
  record_pair makeUnion(const record_pair & pair, const dict_pair & source);
}

void erohin::uniteCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string new_dict_name, first_dict_name, second_dict_name;
  input >> new_dict_name >> first_dict_name >> second_dict_name;
  if (!isNewDictionary(dict_context, new_dict_name))
  {
    throw std::logic_error("unite: dictionary has already existed");
  }
  const dictionary & first_dict = dict_context.at(first_dict_name);
  const dictionary & second_dict = dict_context.at(second_dict_name);
  dictionary temp_dict;
  merge(
    first_dict.cbegin(),
    first_dict.cend(),
    second_dict.cbegin(),
    second_dict.cend(),
    std::inserter(temp_dict, temp_dict.end())
  );
  dictionary new_dict;
  const dict_pair & dict_pair_ref = std::make_pair(first_dict, second_dict);
  using namespace std::placeholders;
  transform(
    temp_dict.cbegin(),
    temp_dict.cend(),
    std::inserter(new_dict, new_dict.end()),
    std::bind(makeUnion, _1, std::cref(dict_pair_ref))
  );
  if (new_dict.empty())
  {
    throw std::underflow_error("unite: Empty union of two dictionaries");
  }
  dict_context[new_dict_name] = std::move(new_dict);
}

namespace erohin
{
  bool compareRecords(const record_pair & lhs, const record_pair & rhs);
  record_pair makeIntersection(const record_pair & pair, const dict_pair & source);
}

void erohin::intersectCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string new_dict_name, first_dict_name, second_dict_name;
  input >> new_dict_name >> first_dict_name >> second_dict_name;
  if (!isNewDictionary(dict_context, new_dict_name))
  {
    throw std::logic_error("intersect: dictionary has already existed");
  }
  const dictionary & first_dict = dict_context.at(first_dict_name);
  const dictionary & second_dict = dict_context.at(second_dict_name);
  dictionary temp_dict;
  std::set_intersection(
    first_dict.cbegin(),
    first_dict.cend(),
    second_dict.cbegin(),
    second_dict.cend(),
    std::inserter(temp_dict, temp_dict.end()),
    compareRecords
  );
  dictionary new_dict;
  const dict_pair & dict_pair_ref = std::make_pair(first_dict, second_dict);
  using namespace std::placeholders;
  transform(
    temp_dict.cbegin(),
    temp_dict.cend(),
    std::inserter(new_dict, new_dict.end()),
    std::bind(makeIntersection, _1, std::cref(dict_pair_ref))
  );
  if (new_dict.empty())
  {
    throw std::underflow_error("differ: Empty difference of two dictionaries");
  }
  dict_context[new_dict_name] = std::move(new_dict);
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

void erohin::printDictionary(const dictionary & dict, std::ostream & output, numformat_t numformat)
{
  size_t total_number = detail::countTotalNumber(dict);
  using namespace std::placeholders;
  std::transform(
    dict.cbegin(),
    dict.cend(),
    std::ostream_iterator< FormattedRecord >(output, "\n"),
    std::bind(createFormattedRecord, std::bind(createRecord< std::string, size_t >, _1), total_number, numformat)
  );
}

void erohin::createSortedDictionary(sorted_dictionary & sorted_dict, const dictionary & source)
{
  std::transform(
    source.cbegin(),
    source.cend(),
    std::inserter(sorted_dict, sorted_dict.end()),
    detail::invertPair< std::string, size_t >
  );
}

void erohin::printSortedDictionary(const sorted_dictionary & sorted_dict, std::ostream & output, numformat_t numformat)
{
  size_t total_number = detail::countTotalNumber(sorted_dict);
  using namespace std::placeholders;
  std::transform(
    sorted_dict.crbegin(),
    sorted_dict.crend(),
    std::ostream_iterator< FormattedRecord >(output, "\n"),
    std::bind(createFormattedRecord, std::bind(createRecord< size_t, std::string >, _1), total_number, numformat)
  );
}

bool erohin::isNewDictionary(const collection & dict_context, const std::string & new_dict_name)
{
  auto found_iter = dict_context.find(new_dict_name);
  return found_iter == dict_context.end();
}

bool erohin::hasDifference(const record_pair & pair, const dictionary & dict)
{
  auto found_iter = dict.find(pair.first);
  return found_iter == dict.end() || pair.second > found_iter->second;
}

erohin::record_pair erohin::makeDifference(const record_pair & pair, const dictionary & dict)
{
  auto found_iter = dict.find(pair.first);
  size_t num = found_iter != dict.end() ?  found_iter->second : 0;
  return std::make_pair(pair.first, pair.second - num);
}

erohin::record_pair erohin::makeUnion(const record_pair & pair, const dict_pair & source)
{
  size_t num = 0;
  auto first_iter = source.first.find(pair.first);
  num += first_iter != source.first.end() ?  first_iter->second : 0;
  auto second_iter = source.second.find(pair.first);
  num += second_iter != source.second.end() ?  second_iter->second : 0;
  return std::make_pair(pair.first, num);
}

bool erohin::compareRecords(const record_pair & lhs, const record_pair & rhs)
{
  return lhs.first < rhs.first;
}

erohin::record_pair erohin::makeIntersection(const record_pair & pair, const dict_pair & source)
{
  return std::make_pair(pair.first, std::min(source.first.at(pair.first), source.second.at(pair.first)));
}
