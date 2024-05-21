#include "dictionary.hpp"

void nikitov::Dictionary::addTranslation(const std::string& word, const std::string& translation)
{
  auto value = data_.insert({ word, detail::Word(translation) });
  if (!value.second)
  {
    value.first->second.getSecondaryTranslation() = translation;
  }
}

void nikitov::Dictionary::addAntonym(const std::string& word, const std::string& antonym)
{
  auto iterToWord = data_.find(word);
  auto iterToAntonym = data_.find(antonym);
  if (iterToWord != data_.cend() && iterToAntonym != data_.cend())
  {
    iterToWord->second.getAntonym() = antonym;
    iterToAntonym->second.getAntonym() = word;
  }
  else
  {
    throw std::logic_error("INVALID COMMAND");
  }
}

void nikitov::Dictionary::deletePrimaryTranslation(const std::string& word)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    if (iterToWord->second.getSecondaryTranslation().empty())
    {
      data_.erase(iterToWord);
    }
    else
    {
      iterToWord->second.getPrimaryTranslation() = iterToWord->second.getSecondaryTranslation();
      iterToWord->second.getSecondaryTranslation() = {};
    }
  }
  else
  {
    throw std::logic_error("<NOTHING TO DO>");
  }
}