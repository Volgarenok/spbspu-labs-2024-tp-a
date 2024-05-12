#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <fstream>
#include <iterator>
#include "word.hpp"
#include "predicates.hpp"
#include "algorithms.hpp"

void novikov::insert(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> key >> value;

  auto& dict = storage.at(dictionary);

  Word::const_words_pair_t match = { std::move(key), std::move(value) };

  if (std::find(dict.begin(), dict.end(), match) != dict.end())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  dict.insert(std::move(match));
}

void novikov::search(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> key >> value;

  const auto& dict = storage.at(dictionary);

  Word::words_pair_t temp = { std::move(key), std::move(value) };
  auto pred = std::bind(containsKeyAndValue, std::placeholders::_1, temp);
  stdx::transform_if(dict.cbegin(), dict.cend(), std::ostream_iterator< Word >{ out, "\n" }, pred, toWord);
}

void novikov::searchKeys(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string key;

  in >> dictionary >> key;

  const auto& dict = storage.at(dictionary);

  Word::words_pair_t temp = { std::move(key), "" };
  auto pred = std::bind(containsKey, std::placeholders::_1, temp);
  stdx::transform_if(dict.cbegin(), dict.cend(), std::ostream_iterator< Word >{ out, "\n" }, pred, toWord);
}

void novikov::searchValues(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string value;

  in >> dictionary >> value;

  const auto& dict = storage.at(dictionary);

  Word::words_pair_t temp = { "", std::move(value) };
  auto pred = std::bind(containsValue, std::placeholders::_1, temp);
  stdx::transform_if(dict.cbegin(), dict.cend(), std::ostream_iterator< Word >{ out, "\n" }, pred, toWord);
}

void novikov::open(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string file;

  in >> dictionary >> file;

  std::ifstream fin(file);

  if (!fin.is_open())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  Dictionary new_dictionary;
  using input_it_t = std::istream_iterator< Word >;
  std::transform(input_it_t{ fin }, input_it_t{}, std::inserter(new_dictionary, new_dictionary.begin()), toPair);
  fin.close();
  storage[dictionary] = std::move(new_dictionary);
}

void novikov::close(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  in >> dictionary;

  if (storage.find(dictionary) == storage.end())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  storage.erase(dictionary);
}

void novikov::print(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  in >> dictionary;
  const auto& dict = storage.at(dictionary);
  std::transform(dict.cbegin(), dict.cend(), std::ostream_iterator< Word >{ out, "\n" }, toWord);
}
