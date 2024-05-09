#include "FrequencyDictionaryCmds.hpp"
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include "StreamGuard.hpp"
#include "DelimiterI.hpp"

void sazanov::insert(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  std::string word;
  in >> word;
  if (!in || collection.find(dict) == collection.end() || word.empty())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  ++collection[dict][word];
}

void sazanov::getFrequency(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  std::string word;
  in >> word;
  if (!in || collection.find(dict) == collection.end() || word.empty())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  out << collection[dict][word] << '\n';
}

void sazanov::erase(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  std::string word;
  in >> word;
  if (!in || collection.find(dict) == collection.end() || word.empty())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  collection[dict].erase(word);
}

void sazanov::getMostFrequent(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  if (!in || collection.find(dict) == collection.end())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  out << std::max_element(collection[dict].cbegin(), collection[dict].cend(),
    [](const std::pair<std::string, std::size_t>& lhs, const std::pair<std::string, std::size_t>& rhs){return lhs.second < rhs.second;})->second;
  out << '\n';
}

void sazanov::size(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  if (!in || collection.find(dict) == collection.end())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  out << collection[dict].size() << '\n';
}

void sazanov::readText(sazanov::DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  std::string fileName;
  in >> fileName;
  if (!in || collection.find(dict) == collection.end() || fileName.empty())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  std::fstream file(fileName);
  if (!file.is_open() || file.eof())
  {
    out << "INVALID COMMAND\n";
    return;
  }
  std::string word;
  while (!file.eof())
  {
    file >> word;
    ++collection[dict][word];
  }
  file.close();
}

void sazanov::save(sazanov::DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  std::string fileName;
  in >> fileName;
  if (!in || collection.find(dict) == collection.end() || fileName.empty())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  std::fstream file(fileName);
  if (!file.is_open() || file.eof())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  for (auto iter = collection[dict].begin(); iter != collection[dict].end(); ++iter)
  {
    file << iter->first << " : " << iter->second << '\n';
  }
  file.close();
}

void sazanov::print(sazanov::DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  if (!in || collection.find(dict) == collection.end())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  for (std::pair< std::string, std::size_t > pair : collection[dict])
  {
    out << pair.first << " : " << pair.second << '\n';
  }
}

void sazanov::readDict(sazanov::DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  std::string fileName;
  in >> fileName;
  if (!in || collection.find(dict) == collection.end() || fileName.empty())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  std::fstream file(fileName);
  if (!file.is_open() || file.eof())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  std::string word;
  std::size_t frequency = 0;
  while (file >> word)
  {
    file >> StrictCaseDelimiterI{':'} >> frequency;
    if (file.fail())
    {
      out << "INVALID FILE\n";
      break;
    }
    collection[dict][word] += frequency;
  }
  file.close();
}

void sazanov::create(sazanov::DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict;
  in >> dict;
  if (!dict.empty())
  {
    collection[dict];
  }
  else
  {
    out << "INVALID COMMAND";
  }
}

void sazanov::merge(sazanov::DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string result;
  std::string dict1;
  std::string dict2;

  in >> result >> dict1 >> dict2;
  if (!in || collection.find(dict1) == collection.end() || collection.find(dict2) == collection.end())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  std::copy(collection[dict1].cbegin(), collection[dict1].cend(), std::inserter(collection[result], collection[result].begin()));
  std::copy_if(collection[dict2].cbegin(), collection[dict2].cend(), std::inserter(collection[result], collection[result].begin()),
    std::bind(copyOrIncreaseFrequency, std::ref(collection[result]), std::placeholders::_1));
}

void sazanov::equal(sazanov::DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string dict1;
  std::string dict2;
  std::string key;

  in >> dict1 >> dict2 >> key;
  if (!in || collection.find(dict1) == collection.end() || collection.find(dict2) == collection.end())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  StreamGuard guard(out);
  out << std::boolalpha << (collection[dict1][key] == collection[dict2][key]);
}

void sazanov::intersect(DictionaryCollection& collection, std::istream& in, std::ostream& out)
{
  std::string result;
  std::string dict1;
  std::string dict2;

  in >> result >> dict1 >> dict2;
  if (!in || collection.find(dict1) == collection.end() || collection.find(dict2) == collection.end())
  {
    out << "INVALID COMMAND\n";
    return;
  }

  std::copy_if(collection[dict1].cbegin(), collection[dict1].cend(), std::inserter(collection[result], collection[result].begin()),
    std::bind(intersectIfOtherDictContein, std::ref(collection[result]), std::ref(collection[dict2]), std::placeholders::_1));
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

bool sazanov::intersectIfOtherDictContein(FrequencyDictionary& result, FrequencyDictionary& other, const std::pair<std::string, std::size_t>& pair)
{
  if (other.find(pair.first) != other.end())
  {
    result[pair.first] += pair.second + other[pair.first];
  }
  return false;
}
