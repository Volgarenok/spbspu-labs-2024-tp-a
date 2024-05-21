#include "dictionary.hpp"

void nikitov::Dictionary::addTranslation(const std::string& word, const std::string& translation)
{
  auto value = data_.insert({ word, detail::Word(translation) });
  if (!value.second)
  {
    value.first->second.addTranslation(translation);
  }
}

void nikitov::Dictionary::addAntonym(const std::string& word, const std::string& antonym)
{
  auto iterToWord = data_.find(word);
  auto iterToAntonym = data_.find(antonym);
  if (iterToWord != data_.cend() && iterToAntonym != data_.cend())
  {
    iterToWord->second.addAntonym(antonym);
    iterToAntonym->second.addAntonym(word);
  }
  else
  {
    throw std::logic_error("INVALID COMMAND");
  }
}

void nikitov::Dictionary::deleteTranslation(const std::string& word)
{
  data_.erase(word);
}