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
  Word::const_words_pair_t temp = { std::move(key), std::move(value) };

  if (std::find(dict.cbegin(), dict.cend(), temp) != dict.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  dict.insert(std::move(temp));
}

void novikov::search(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> key >> value;

  const auto& dict = storage.at(dictionary);
  Word::words_pair_t temp = { std::move(key), std::move(value) };
  auto pred = std::bind(containsKeyAndValue, std::placeholders::_1, std::cref(temp));
  stdx::transform_if(dict.cbegin(), dict.cend(), std::ostream_iterator< Word >{ out, "\n" }, pred, toWord);
}

void novikov::searchKeys(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string key;

  in >> dictionary >> key;

  const auto& dict = storage.at(dictionary);
  Word::words_pair_t temp = { std::move(key), "" };
  auto pred = std::bind(containsKey, std::placeholders::_1, std::cref(temp));
  stdx::transform_if(dict.cbegin(), dict.cend(), std::ostream_iterator< Word >{ out, "\n" }, pred, toWord);
}

void novikov::searchValues(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  std::string value;

  in >> dictionary >> value;

  const auto& dict = storage.at(dictionary);
  Word::words_pair_t temp = { "", std::move(value) };
  auto pred = std::bind(containsValue, std::placeholders::_1, std::cref(temp));
  stdx::transform_if(dict.cbegin(), dict.cend(), std::ostream_iterator< Word >{ out, "\n" }, pred, toWord);
}

void novikov::remove(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> key >> value;

  auto& dict = storage.at(dictionary);
  Word::words_pair_t temp = { std::move(key), std::move(value) };
  auto pred = std::bind(containsKeyAndValue, std::placeholders::_1, std::cref(temp));

  if (std::find_if(dict.cbegin(), dict.cend(), pred) == dict.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  stdx::erase_if(dict, pred);
}

void novikov::removeKeys(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string key;

  in >> dictionary >> key;

  auto& dict = storage.at(dictionary);
  Word::words_pair_t temp = { std::move(key), "" };
  auto pred = std::bind(containsKey, std::placeholders::_1, std::cref(temp));

  if (std::find_if(dict.begin(), dict.end(), pred) == dict.end())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  stdx::erase_if(dict, pred);
}

void novikov::removeValues(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string key;
  std::string value;

  in >> dictionary >> value;

  auto& dict = storage.at(dictionary);
  Word::words_pair_t temp = { "", std::move(value) };
  auto pred = std::bind(containsValue, std::placeholders::_1, std::cref(temp));

  if (std::find_if(dict.cbegin(), dict.cend(), pred) == dict.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  stdx::erase_if(dict, pred);
}

void novikov::open(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string file;

  in >> dictionary >> file;
  std::ifstream fin(file);

  if (storage.find(dictionary) != storage.cend() || !fin.is_open())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  Dictionary new_dictionary;
  using input_it_t = std::istream_iterator< Word >;
  std::transform(input_it_t{ fin }, input_it_t{}, std::inserter(new_dictionary, new_dictionary.begin()), toPair);
  fin.close();
  storage[dictionary] = std::move(new_dictionary);
}

void novikov::save(const DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string file;

  in >> dictionary >> file;

  const auto& dict = storage.at(dictionary);
  std::ofstream fout(file);

  if (!fout.is_open())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  using output_it_t = std::ostream_iterator< Word >;
  std::transform(dict.cbegin(), dict.cend(), output_it_t{ fout, "\n" }, toWord);
  fout.close();
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
  using output_it_t = std::ostream_iterator< Word >;
  std::transform(dict.cbegin(), dict.cend(), output_it_t{ out, "\n" }, toWord);
}

void novikov::size(const DictionariesStorage& storage, std::istream& in, std::ostream& out)
{
  std::string dictionary;
  in >> dictionary;
  out << storage.at(dictionary).size() << "\n";
}
