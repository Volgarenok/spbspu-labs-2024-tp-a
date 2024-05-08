#include "FrequencyDictionaryCmds.hpp"
#include <unordered_map>
#include <sstream>
#include <algorithm>

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
