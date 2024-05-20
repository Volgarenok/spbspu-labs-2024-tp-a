#include "dictionary.hpp"

void nikitov::Dictionary::addWord(const std::string& word, const std::string& translation, const std::string& antonym)
{
  data_.insert({ word, detail::Word(translation, antonym) });
}