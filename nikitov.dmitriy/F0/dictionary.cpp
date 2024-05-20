#include "dictionary.hpp"

void nikitov::Dictionary::addWord(const std::string& word, const std::string& translation, const std::string& antonym)
{
  data_.insert({ word, detail::Word(translation, antonym) });
}

void nikitov::Dictionary::deleteWord(const std::string& word)
{
  data_.erase(word);
}

void nikitov::Dictionary::editWord(const std::string& word, const std::string& translation, const std::string& antonym)
{
  detail::Word toEdit = data_.at(word);
  toEdit.translation_ = translation;
  toEdit.antonym_ = antonym;
}