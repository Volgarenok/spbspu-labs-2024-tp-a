#include "dictionary.hpp"

void chernikova::Dictionary::insert(const std::string& word, const std::set< std::string >& translations)
{
  data_.insert({ word, translations });
}