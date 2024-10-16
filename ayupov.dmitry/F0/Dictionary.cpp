#include "Dictionary.hpp"

#include <istream>
#include <algorithm>
#include <functional>
#include <cctype>

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

bool ayupov::ARDictionary::operator==(const ARDictionary& other)
{
  return this->dictionary == other.dictionary;
}

std::istream& ayupov::operator>>(std::istream& in, ARDictionary& dict)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string word;
  std::string translation;
  in >> word >> translation;
  if (isWord(word) && isTranslation(translation))
  {
    dict.dictionary[word].insert(translation);
  }
  return in;
}

bool ayupov::isWord(const std::string& word)
{
  auto result{ std::find_if_not(word.begin(), word.end(), isalpha)};
  if (result == word.end())
  {
    return true;
  }
  return false;
}

bool ayupov::isTranslation(const std::string& translation)
{
  std::locale locale("RUSSIAN");
  auto result{ std::find_if_not(translation.begin(), translation.end(), std::bind(isalpha, std::placeholders::_1, locale))};
  if (result == translation.end())
  {
    return true;
  }
  return false;
}
