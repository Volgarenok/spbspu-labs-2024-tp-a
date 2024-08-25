#include "collection_commands.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <limits>
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

namespace erohin
{
  struct UniqueNumElemFunctor
  {
    size_t count;
    size_t current_count = 0;
    size_t prev_num = 0;
    bool operator()(const std::pair< size_t, std::string > & pair);
  };
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
  size_t count = std::count_if(sorted_dict.crbegin(), sorted_dict.crend(), UniqueNumElemFunctor{ num });
  Dictionary temp_dict;
  std::transform(
    sorted_dict.crbegin(),
    std::next(sorted_dict.crbegin(), count),
    std::inserter(temp_dict.records, temp_dict.records.end()),
    detail::invertPair< size_t, std::string >
  );
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
  size_t count = std::count_if(sorted_dict.cbegin(), sorted_dict.cend(), UniqueNumElemFunctor{ num });
  Dictionary temp_dict;
  std::transform(
    sorted_dict.cbegin(),
    std::next(sorted_dict.cbegin(), count),
    std::inserter(temp_dict.records, temp_dict.records.end()),
    detail::invertPair< size_t, std::string >
  );
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  using record_pair = std::pair< std::string, size_t >;
  using dict_pair = std::pair< Dictionary, Dictionary >;
  void makeDifference(Dictionary & dict, const dict_pair & source);
  bool ifNumberGreater(const record_pair & pair, const Dictionary & source);
  record_pair countDifference(const record_pair & pair, const Dictionary & source);
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
  makeDifference(temp_dict, std::make_pair(first_dict, second_dict));
  if (temp_dict.records.empty())
  {
    throw std::underflow_error("differ: empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  void makeUnion(Dictionary & dict, const dict_pair & source);
  record_pair countUnion(const record_pair & pair, const dict_pair & source);
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
  const Dictionary & second_dict = dict_context.at(dict_name[2]);
  Dictionary temp_dict;
  makeUnion(temp_dict, std::make_pair(first_dict, second_dict));
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  void makeIntersection(Dictionary & dict, const dict_pair & source);
  record_pair countIntersection(const record_pair & pair, const dict_pair & source);
  bool compareRecordPair(const record_pair & lhs, const record_pair & rhs);
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
  makeIntersection(temp_dict, std::make_pair(first_dict, second_dict));
  if (temp_dict.records.empty())
  {
    throw std::underflow_error("differ: empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(temp_dict);
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
  size_t max_size = std::numeric_limits< size_t >::max();
  std::string word;
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

bool erohin::UniqueNumElemFunctor::operator()(const std::pair< size_t, std::string > & pair)
{
  if (pair.first != prev_num)
  {
    ++current_count;
    prev_num = pair.first;
  }
  return current_count <= count;
}

void erohin::makeDifference(Dictionary & dict, const dict_pair & source)
{
  using namespace std::placeholders;
  Dictionary temp_dict;
  copy_if(
    source.first.records.cbegin(),
    source.first.records.cend(),
    std::inserter(temp_dict.records, temp_dict.records.end()),
    std::bind(ifNumberGreater, _1, std::cref(source.second))
  );
  transform(
    temp_dict.records.cbegin(),
    temp_dict.records.cend(),
    std::inserter(dict.records, dict.records.end()),
    std::bind(countDifference, _1, std::cref(source.second))
  );
}

bool erohin::ifNumberGreater(const record_pair & pair, const Dictionary & source)
{
  auto found_iter = source.records.find(pair.first);
  return (found_iter == source.records.cend() || pair.second > found_iter->second);
}

erohin::record_pair erohin::countDifference(const record_pair & pair, const Dictionary & source)
{
  auto found_iter = source.records.find(pair.first);
  size_t num = pair.second;
  num -= (found_iter != source.records.cend()) ? found_iter->second : 0;
  return std::make_pair(pair.first, num);
}

void erohin::makeUnion(Dictionary & dict, const dict_pair & source)
{
  using namespace std::placeholders;
  Dictionary temp_dict;
  std::merge(
    source.first.records.cbegin(),
    source.first.records.cend(),
    source.second.records.cbegin(),
    source.second.records.cend(),
    std::inserter(temp_dict.records, temp_dict.records.end())
  );
  std::transform(
    temp_dict.records.cbegin(),
    temp_dict.records.cend(),
    std::inserter(dict.records, dict.records.end()),
    std::bind(countUnion, _1, std::cref(source))
  );
}

erohin::record_pair erohin::countUnion(const record_pair & pair, const dict_pair & source)
{
  auto found_iter = source.first.records.find(pair.first);
  size_t num = (found_iter != source.first.records.cend()) ? found_iter->second : 0;
  found_iter = source.second.records.find(pair.first);
  num += (found_iter != source.second.records.cend()) ? found_iter->second : 0;
  return std::make_pair(pair.first, num);
}

void erohin::makeIntersection(Dictionary & dict, const dict_pair & source)
{
  using namespace std::placeholders;
  Dictionary temp_dict;
  std::set_intersection(
    source.first.records.cbegin(),
    source.first.records.cend(),
    source.second.records.cbegin(),
    source.second.records.cend(),
    std::inserter(temp_dict.records, temp_dict.records.end()),
    compareRecordPair
  );
  std::transform(
    temp_dict.records.cbegin(),
    temp_dict.records.cend(),
    std::inserter(dict.records, dict.records.end()),
    std::bind(countIntersection, _1, std::cref(source))
  );
}

erohin::record_pair erohin::countIntersection(const record_pair & pair, const dict_pair & source)
{
  size_t num = std::min(source.first.records.at(pair.first), source.second.records.at(pair.first));
  return std::make_pair(pair.first, num);
}

bool erohin::compareRecordPair(const record_pair & lhs, const record_pair & rhs)
{
  return lhs.first < rhs.first;
}
