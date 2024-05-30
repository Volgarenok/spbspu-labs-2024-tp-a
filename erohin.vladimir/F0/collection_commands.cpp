#include "collection_commands.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>
#include <forward_list>
#include "format.hpp"
#include "dictionary_record.hpp"
#include "number_format.hpp"

void erohin::addTextCommand(texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string text_name[2];
  input >> text_name[0] >> text_name[1];
  auto iter_pair = text_context.insert(std::make_pair(text_name[0], text_name[1]));
  if (!iter_pair.second)
  {
    throw std::logic_error("addtext: bad insertion into texts source");
  }
}

void erohin::removeTextCommand(texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string text_name;
  input >> text_name;
  auto found_iter = text_context.find(text_name);
  if (found_iter == text_context.end())
  {
    throw std::logic_error("removetext: bad removal from texts source");
  }
  text_context.erase(found_iter);
}

namespace erohin
{
  bool isNewDictionary(const collection & dict_context, const std::string & new_dict_name);
  void createDictionary(Dictionary & dict, const std::string & file_name);
}

void erohin::createDictCommand(collection & dict_context, const texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string name[2];
  input >> name[0] >> name[1];
  if (!isNewDictionary(dict_context, name[0]))
  {
    throw std::logic_error("creadict: dictionary has already existed");
  }
  Dictionary temp_dict;
  createDictionary(temp_dict, text_context.at(name[1]));
  dict_context[name[0]] = std::move(temp_dict);
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
  void printDictionary(const Dictionary & dict, std::ostream & output, numformat_t numformat);
}

void erohin::printCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const Dictionary & dict = dict_context.at(dict_name);
  printDictionary(dict, output, numformat);
}

void erohin::countCommand(const collection & dict_context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  const Dictionary & dict = dict_context.at(dict_name);
  size_t total_number = detail::countTotalNumber(dict.records);
  size_t unique_number = dict.records.size();
  output << "words: " << total_number << "; unique words: " << unique_number << "\n";
}

namespace erohin
{
  using sorted_dictionary = std::multimap< size_t, std::string >;
  void createSortedDictionary(sorted_dictionary & sorted_dict, const Dictionary & source);
  void printSortedDictionary(const sorted_dictionary & sorted_dict, std::ostream & output, numformat_t numformat);
}

void erohin::sortCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const Dictionary & dict = dict_context.at(dict_name);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  printSortedDictionary(sorted_dict, output, numformat);
}

void erohin::findCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string name[2];
  input >> name[0] >> name[1];
  const Dictionary & dict = dict_context.at(name[0]);
  auto found_iter = dict.records.find(name[1]);
  if (found_iter != dict.records.cend())
  {
    size_t total_number = detail::countTotalNumber(dict.records);
    output << FormattedRecord(Record(*found_iter), total_number, numformat) << "\n";
  }
  else
  {
    throw std::logic_error("find: cannot find word");
  }
}

void erohin::topCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[2];
  size_t num = 0;
  input >> dict_name[0] >> dict_name[1] >> num;
  if (!input || !isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("top: wrong argument input");
  }
  const Dictionary & dict = dict_context.at(dict_name[1]);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  Dictionary temp_dict;
  detail::insertNumRecords(temp_dict.records, num, sorted_dict.crbegin(), sorted_dict.crend());
  dict_context[dict_name[0]] = std::move(temp_dict);
}

void erohin::bottomCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[2];
  size_t num = 0;
  input >> dict_name[0] >> dict_name[1] >> num;
  if (!input || !isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("bottom: wrong argument input");
  }
  const Dictionary & dict = dict_context.at(dict_name[1]);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  Dictionary temp_dict;
  detail::insertNumRecords(temp_dict.records, num, sorted_dict.cbegin(), sorted_dict.cend());
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  bool hasDifference(const record_pair & pair, const Dictionary & dict);
  record_pair makeDifference(const record_pair & pair, const Dictionary & dict);
}

void erohin::differCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("differ: dictionary has already existed");
  }
  const Dictionary & first_dict = dict_context.at(dict_name[1]);
  const Dictionary & second_dict = dict_context.at(dict_name[2]);
  Dictionary temp_dict;
  using namespace std::placeholders;
  copy_if(
    first_dict.records.cbegin(),
    first_dict.records.cend(),
    std::inserter(temp_dict.records, temp_dict.records.end()),
    std::bind(hasDifference, _1, std::cref(second_dict))
  );
  Dictionary new_dict;
  transform(
    temp_dict.records.cbegin(),
    temp_dict.records.cend(),
    std::inserter(new_dict.records, new_dict.records.end()),
    std::bind(makeDifference, _1, std::cref(second_dict))
  );
  if (new_dict.records.empty())
  {
    throw std::underflow_error("differ: empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(new_dict);
}

namespace erohin
{
  using dict_pair = std::pair< Dictionary, Dictionary >;
  record_pair makeUnion(const record_pair & pair, const dict_pair & source);
}

void erohin::uniteCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("unite: dictionary has already existed");
  }
  const Dictionary & first_dict = dict_context.at(dict_name[1]);
  const Dictionary & second_dict = dict_context.at(dict_name[1]);
  Dictionary temp_dict;
  merge(
    first_dict.records.cbegin(),
    first_dict.records.cend(),
    second_dict.records.cbegin(),
    second_dict.records.cend(),
    std::inserter(temp_dict.records, temp_dict.records.end())
  );
  Dictionary new_dict;
  const dict_pair & dict_pair_ref = std::make_pair(first_dict, second_dict);
  using namespace std::placeholders;
  transform(
    temp_dict.records.cbegin(),
    temp_dict.records.cend(),
    std::inserter(new_dict.records, new_dict.records.end()),
    std::bind(makeUnion, _1, std::cref(dict_pair_ref))
  );
  if (new_dict.records.empty())
  {
    throw std::underflow_error("unite: empty union of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(new_dict);
}

namespace erohin
{
  bool compareRecords(const record_pair & lhs, const record_pair & rhs);
  record_pair makeIntersection(const record_pair & pair, const dict_pair & source);
}

void erohin::intersectCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("intersect: dictionary has already existed");
  }
  const Dictionary & first_dict = dict_context.at(dict_name[1]);
  const Dictionary & second_dict = dict_context.at(dict_name[2]);
  Dictionary temp_dict;
  std::set_intersection(
    first_dict.records.cbegin(),
    first_dict.records.cend(),
    second_dict.records.cbegin(),
    second_dict.records.cend(),
    std::inserter(temp_dict.records, temp_dict.records.end()),
    compareRecords
  );
  Dictionary new_dict;
  const dict_pair & dict_pair_ref = std::make_pair(first_dict, second_dict);
  using namespace std::placeholders;
  transform(
    temp_dict.records.cbegin(),
    temp_dict.records.cend(),
    std::inserter(new_dict.records, new_dict.records.end()),
    std::bind(makeIntersection, _1, std::cref(dict_pair_ref))
  );
  if (new_dict.records.empty())
  {
    throw std::underflow_error("differ: empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(new_dict);
}

bool erohin::isNewDictionary(const collection & dict_context, const std::string & new_dict_name)
{
  auto found_iter = dict_context.find(new_dict_name);
  return found_iter == dict_context.end();
}

void erohin::createDictionary(Dictionary & dict, const std::string & file_name)
{
  std::fstream file;
  file.open(file_name);
  if (!file)
  {
    throw std::runtime_error("File reading error");
  }
  Dictionary temp_dict;
  std::string word;
  size_t max_size = std::numeric_limits< size_t >::max();
  file >> WordInContextFormat{ word, max_size};
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    else
    {
      ++temp_dict.records[word];
    }
    file >> WordInContextFormat{ word, max_size};
  }
  dict = std::move(temp_dict);
  file.close();
}

void erohin::printDictionary(const Dictionary & dict, std::ostream & output, numformat_t numformat)
{
  size_t total_number = detail::countTotalNumber(dict.records);
  using namespace std::placeholders;
  std::transform(
    dict.records.cbegin(),
    dict.records.cend(),
    std::ostream_iterator< FormattedRecord >(output, "\n"),
    std::bind(createFormattedRecord, std::bind(createRecord< std::string, size_t >, _1), total_number, numformat)
  );
}

void erohin::createSortedDictionary(sorted_dictionary & sorted_dict, const Dictionary & source)
{
  std::transform(
    source.records.cbegin(),
    source.records.cend(),
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

bool erohin::hasDifference(const record_pair & pair, const Dictionary & dict)
{
  auto found_iter = dict.records.find(pair.first);
  return found_iter == dict.records.end() || pair.second > found_iter->second;
}

erohin::record_pair erohin::makeDifference(const record_pair & pair, const Dictionary & dict)
{
  auto found_iter = dict.records.find(pair.first);
  size_t num = found_iter != dict.records.end() ?  found_iter->second : 0;
  return std::make_pair(pair.first, pair.second - num);
}

erohin::record_pair erohin::makeUnion(const record_pair & pair, const dict_pair & source)
{
  size_t num = 0;
  auto first_iter = source.first.records.find(pair.first);
  num += first_iter != source.first.records.end() ?  first_iter->second : 0;
  auto second_iter = source.second.records.find(pair.first);
  num += second_iter != source.second.records.end() ?  second_iter->second : 0;
  return std::make_pair(pair.first, num);
}

bool erohin::compareRecords(const record_pair & lhs, const record_pair & rhs)
{
  return lhs.first < rhs.first;
}

erohin::record_pair erohin::makeIntersection(const record_pair & pair, const dict_pair & source)
{
  return std::make_pair(pair.first, std::min(source.first.records.at(pair.first), source.second.records.at(pair.first)));
}
