#include "FrequencyDictionaryCmds.hpp"
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <StreamGuard.hpp>
#include "DictionaryLineIO.hpp"
#include "SupportCmds.hpp"

bool compareFrequency(const std::pair< std::string, size_t >& lhs, const std::pair< std::string, size_t >& rhs);
bool copyOrIncreaseFrequency(sazanov::FrequencyDictionary& result, const std::pair< std::string, size_t >& pair);
bool isDictContein(sazanov::FrequencyDictionary& dict, const std::pair< std::string, size_t >& pair);
std::pair< std::string, size_t > increaseFrequency(sazanov::FrequencyDictionary& other, const std::pair< std::string, size_t >& pair);
sazanov::DictionaryLineO getDictionaryLineO(const std::pair< std::string, size_t >& pair);

void sazanov::insert(DictionaryCollection& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  std::string word;
  in >> word;

  ++collection.at(dict)[word];
}

void sazanov::getFrequency(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  std::string word;
  in >> word;

  out << collection.at(dict)[word] << '\n';
}

void sazanov::erase(DictionaryCollection& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  std::string word;
  in >> word;

  collection.at(dict).erase(word);
}

void sazanov::getMostFrequent(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  if (collection.at(dict).empty())
  {
    throw std::logic_error("INVALID COMMAND");
  }
  out << std::max_element(collection[dict].cbegin(), collection[dict].cend(), compareFrequency)->first << '\n';
}

void sazanov::size(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;

  out << collection.at(dict).size() << '\n';
}

void sazanov::readText(DictionaryCollection& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  std::string fileName;
  in >> fileName;

  std::fstream file(fileName);
  if (!file.is_open() || file.peek() == EOF)
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }

  std::string word;
  while (!file.eof())
  {
    file >> word;
    ++collection.at(dict)[word];
  }
}

void sazanov::save(DictionaryCollection& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  std::string fileName;
  in >> fileName;

  std::fstream file(fileName);
  if (!file.is_open())
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }

  using output_it = std::ostream_iterator< DictionaryLineO >;
  std::transform(collection.at(dict).begin(), collection.at(dict).end(), output_it{file, "\n"}, getDictionaryLineO);
}

void sazanov::readDict(DictionaryCollection& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  std::string fileName;
  in >> fileName;

  if (!in || collection.find(dict) == collection.end() || !isCorrectFile(fileName))
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }
  readDict(dict, fileName, collection);
}

void sazanov::print(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;

  using output_it = std::ostream_iterator< DictionaryLineO >;
  std::transform(collection.at(dict).begin(), collection.at(dict).end(), output_it(out, "\n"), getDictionaryLineO);
}

void sazanov::create(DictionaryCollection& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }
  collection[dict];
}

void sazanov::merge(DictionaryCollection& collection, std::istream& in)
{
  std::string result;
  std::string dict1;
  std::string dict2;

  in >> result >> dict1 >> dict2;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }

  std::copy(collection.at(dict1).cbegin(), collection.at(dict1).cend(), std::inserter(collection[result], collection[result].begin()));
  std::copy_if(collection.at(dict2).cbegin(), collection.at(dict2).cend(), std::inserter(collection[result], collection[result].begin()),
    std::bind(copyOrIncreaseFrequency, std::ref(collection[result]), std::placeholders::_1));
}

void sazanov::equal(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict1;
  std::string dict2;
  std::string key;

  in >> dict1 >> dict2 >> key;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }

  StreamGuard guard(out);
  out << std::boolalpha;
  if (!isDictContein(collection.at(dict1), {key, 0}) || !isDictContein(collection.at(dict2), {key, 0}))
  {
    out << (isDictContein(collection[dict1], {key, 0}) == isDictContein(collection[dict2], {key, 0})) << '\n';
    return;
  }
  out << (collection[dict1][key] == collection[dict2][key]) << '\n';
}

void sazanov::intersect(DictionaryCollection& collection, std::istream& in)
{
  std::string result;
  std::string dict1;
  std::string dict2;

  in >> result >> dict1 >> dict2;
  if (!in)
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }

  FrequencyDictionary temp;
  std::copy_if(collection.at(dict1).cbegin(), collection.at(dict1).cend(), std::inserter(temp, temp.begin()),
    std::bind(isDictContein, collection.at(dict2), std::placeholders::_1));
  std::transform(temp.cbegin(), temp.cend(), std::inserter(collection[result], collection[result].begin()),
    std::bind(increaseFrequency, collection[dict2], std::placeholders::_1));
}

bool copyOrIncreaseFrequency(sazanov::FrequencyDictionary& result, const std::pair< std::string, size_t >& pair)
{
  if (result.find(pair.first) == result.end())
  {
    return true;
  }
  result[pair.first] += pair.second;
  return false;
}

bool compareFrequency(const std::pair< std::string, size_t >& lhs,
  const std::pair< std::string, size_t >& rhs)
{
  return lhs.second < rhs.second;;
}

bool isDictContein(sazanov::FrequencyDictionary& dict, const std::pair< std::string, size_t >& pair)
{
  return dict.find(pair.first) != dict.end();
}

std::pair< std::string, std::size_t > increaseFrequency(sazanov::FrequencyDictionary& other,
  const std::pair< std::string, size_t >& pair)
{
  return {pair.first, pair.second + other[pair.first]};
}

sazanov::DictionaryLineO getDictionaryLineO(const std::pair< std::string, size_t >& pair)
{
  return sazanov::DictionaryLineO{pair};
}
