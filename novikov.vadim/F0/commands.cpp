#include "commands.hpp"
#include <fstream>
#include <string>
#include <cmath>
#include "word.hpp"
#include "customAlgorithms.hpp"

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

void novikov::create(DictionariesStorage& storage, std::istream& in)
{
  std::string new_dictionary;
  in >> new_dictionary;

  if (storage.find(new_dictionary) != storage.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  storage[new_dictionary] = {};
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

  if (!fin.eof())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

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

void novikov::merge(DictionariesStorage& storage, std::istream& in)
{
  std::string new_dictionary;
  double count_dbl;
  std::vector< std::string > dictionaries;

  in >> new_dictionary >> count_dbl;

  if (!in || (std::floor(count_dbl) != count_dbl) || count_dbl < 2.0)
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  size_t count = count_dbl;

  using input_it_t = std::istream_iterator< std::string >;
  std::copy_n(input_it_t{ in }, count, std::back_inserter(dictionaries));

  if (storage.find(new_dictionary) != storage.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  Dictionary temp;
  for (const auto& i : dictionaries)
  {
    auto pred = std::bind(notFound, temp, std::placeholders::_1);
    auto curr = storage.at(i);
    std::copy_if(curr.cbegin(), curr.cend(), std::inserter(temp, temp.begin()), pred);
  }
  storage[new_dictionary] = std::move(temp);
}

void novikov::intersect(DictionariesStorage& storage, std::istream& in)
{
  std::string new_dictionary;
  double count_dbl;
  std::vector< std::string > dictionaries;

  in >> new_dictionary >> count_dbl;

  if (!in || (std::floor(count_dbl) != count_dbl) || count_dbl < 2.0)
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  size_t count = count_dbl;

  using input_it_t = std::istream_iterator< std::string >;
  std::copy_n(input_it_t{ in }, count, std::back_inserter(dictionaries));

  if (storage.find(new_dictionary) != storage.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  Dictionary temp;
  auto curr = storage.at(*dictionaries.cbegin());
  std::copy(curr.cbegin(), curr.cend(), std::inserter(temp, temp.begin()));
  for (auto i = dictionaries.cbegin() + 1; i != dictionaries.cend(); ++i)
  {
    eraseIf(temp, std::bind(notFoundInBoth, temp, storage.at(*i), std::placeholders::_1));
  }
  storage[new_dictionary] = std::move(temp);
}

void novikov::filter(DictionariesStorage& storage, std::istream& in)
{
  std::string new_dictionary;
  std::string dictionary1;
  std::string dictionary2;

  in >> new_dictionary >> dictionary1 >> dictionary2;

  if (storage.find(new_dictionary) != storage.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  Dictionary temp;
  auto pred = std::bind(notFound, storage.at(dictionary2), std::placeholders::_1);
  auto curr = storage.at(dictionary1);
  std::copy_if(curr.cbegin(), curr.cend(), std::inserter(temp, temp.begin()), pred);
  storage[new_dictionary] = std::move(temp);
}

void novikov::invert(DictionariesStorage& storage, std::istream& in)
{
  std::string dictionary;
  std::string new_dictionary;

  in >> dictionary >> new_dictionary;

  if (storage.find(new_dictionary) != storage.cend())
  {
    throw std::invalid_argument("<INVALID_COMMAND>");
  }

  Dictionary temp;
  auto invertor = invertPair< std::string, std::string >;
  auto curr = storage.at(dictionary);
  std::transform(curr.begin(), curr.end(), std::inserter(temp, temp.begin()), invertor);
  storage[new_dictionary] = std::move(temp);
}
