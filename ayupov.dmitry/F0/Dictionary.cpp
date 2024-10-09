#include "Dictionary.hpp"

bool ayupov::ARDictionary::insert(const std::string& word, const std::string& translation)
{
  return dictionary[word].insert(translation).second;
}