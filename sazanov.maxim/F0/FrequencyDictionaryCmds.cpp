#include "FrequencyDictionaryCmds.hpp"
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <StreamGuard.hpp>
#include "DictionaryLineIO.hpp"

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

  out << std::max_element(collection.at(dict).cbegin(), collection[dict].cend(), compareFrequency)->first << '\n';
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
  file.close();
}

void sazanov::save(DictionaryCollection& collection, std::istream& in)
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

  for (const auto& pair : collection.at(dict))
  {
    file << DictionaryLineIO{pair.first, pair.second} << '\n';
  }
  file.close();
}

void sazanov::print(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;

  for (const auto& pair : collection.at(dict))
  {
    out << DictionaryLineIO{pair.first, pair.second} << '\n';
  }
}

void sazanov::readDict(DictionaryCollection& collection, std::istream& in)
{
  std::string dict;
  in >> dict;
  std::string fileName;
  in >> fileName;

  std::fstream file(fileName);
  if (!in || !file.is_open() || file.peek() == EOF)
  {
    throw std::logic_error("<INVALID ARGUMENTS>");
  }

  std::string word;
  std::size_t frequency = 0;
  FrequencyDictionary temp;
  while (file.peek() != EOF)
  {
    file >> DictionaryLineI{word, frequency};
    if (file.get() != '\n' || file.fail())
    {
      throw std::logic_error("<INVALID FILE>");
    }
    temp[word] += frequency;
  }
  collection[dict] = temp;
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

  std::copy(collection.at(dict1).cbegin(), collection[dict1].cend(), std::inserter(collection[result], collection[result].begin()));
  std::copy_if(collection.at(dict2).cbegin(), collection[dict2].cend(), std::inserter(collection[result], collection[result].begin()),
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
  if (!isDictContein(collection[dict1], {key, 0}) || !isDictContein(collection[dict2], {key, 0}))
  {
    out << (isDictContein(collection[dict1], {key, 0}) == isDictContein(collection[dict2], {key, 0}));
    return;
  }
  out << (collection.at(dict1)[key] == collection.at(dict2)[key]);
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
  std::copy_if(collection.at(dict1).cbegin(), collection[dict1].cend(), std::inserter(temp, temp.begin()),
    std::bind(isDictContein, collection.at(dict2), std::placeholders::_1));
  std::transform(temp.cbegin(), temp.cend(), std::inserter(collection[result], collection[result].begin()),
    std::bind(increaseFrequency, collection[dict2], std::placeholders::_1));
}

bool sazanov::copyOrIncreaseFrequency(FrequencyDictionary& result, const std::pair<std::string, std::size_t>& pair)
{
  if (result.find(pair.first) == result.end())
  {
    return true;
  }
  result[pair.first] += pair.second;
  return false;
}

bool sazanov::compareFrequency(const std::pair<std::string, std::size_t>& lhs,
  const std::pair<std::string, std::size_t>& rhs)
{
  return lhs.second < rhs.second;;
}

bool sazanov::isDictContein(FrequencyDictionary& dict, const std::pair<std::string, std::size_t>& pair)
{
  return dict.find(pair.first) != dict.end();
}

std::pair< std::string, std::size_t > sazanov::increaseFrequency(FrequencyDictionary& other,
  const std::pair<std::string, std::size_t>& pair)
{
  return {pair.first, pair.second + other[pair.first]};
}
