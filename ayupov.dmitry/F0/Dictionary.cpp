#include "Dictionary.hpp"

bool ayupov::ARDictionary::insert(const std::string& word, const std::string& translation)
{
  return dictionary[word].insert(translation).second;
}

const std::set<std::string>* ayupov::ARDictionary::search(const std::string& word) const
{
  auto result = dictionary.find(word);
  if (result == dictionary.end())
  {
    return nullptr;
  }
  return &(*result).second;
}

bool ayupov::ARDictionary::remove(const std::string& word)
{
  return dictionary.erase(word);
}

bool ayupov::ARDictionary::removeTranlation(const std::string& word, const std::string& translation)
{
  return dictionary[word].erase(translation);
}
