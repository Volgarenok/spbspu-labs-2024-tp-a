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
  if (iterToWord != data_.end() && iterToAntonym != data_.end())
  {
    iterToWord->second.getAntonym() = antonym;
    iterToAntonym->second.getAntonym() = word;
  }
  else
  {
    throw std::logic_error("INVALID COMMAND");
  }
}

void nikitov::Dictionary::editPrimaryTranslation(const std::string& word, const std::string& translation)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    iterToWord->second.getPrimaryTranslation() = translation;
  }
}

void nikitov::Dictionary::editSecondaryTranslation(const std::string& word, const std::string& translation)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    iterToWord->second.getSecondaryTranslation() = translation;
  }
}

void nikitov::Dictionary::deletePrimaryTranslation(const std::string& word)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    if (iterToWord->second.getSecondaryTranslation().empty())
    {
      deleteAntonym(word);
      data_.erase(iterToWord);
    }
    else
    {
      std::swap(iterToWord->second.getPrimaryTranslation(), iterToWord->second.getSecondaryTranslation());
      iterToWord->second.getSecondaryTranslation() = {};
    }
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::Dictionary::deleteSecondaryTranslation(const std::string& word)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    if (iterToWord->second.getSecondaryTranslation().empty())
    {
      throw std::logic_error("<NOTHIND TO DO>");
    }
    else
    {
      iterToWord->second.getSecondaryTranslation() = {};
    }
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void nikitov::Dictionary::deleteAntonym(const std::string& word)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    auto iterToAntonym = data_.find(iterToWord->second.getAntonym());
    iterToWord->second.getAntonym() = {};
    if (iterToAntonym != data_.end() && iterToAntonym->second.getAntonym() == word)
    {
      iterToAntonym->second.getAntonym() = {};
    }
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}