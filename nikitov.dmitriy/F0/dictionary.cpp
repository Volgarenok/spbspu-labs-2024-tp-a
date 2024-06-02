#include "dictionary.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
#include <delimiter.hpp>

void nikitov::Dictionary::addTranslation(const std::string& word, const std::string& translation)
{
  auto iterToWord = data_.find(word);
  if (iterToWord == data_.end())
  {
    data_.insert({ word, detail::Word(translation) });
  }
  else
  {
    if (iterToWord->second.secondaryTranslation.empty())
    {
      iterToWord->second.secondaryTranslation = translation;
    }
    else
    {
      throw std::logic_error("<ERROR: NOTHING TO DO>");
    }
  }
}

void nikitov::Dictionary::editPrimaryTranslation(const std::string& word, const std::string& translation)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    iterToWord->second.primaryTranslation = translation;
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

void nikitov::Dictionary::editSecondaryTranslation(const std::string& word, const std::string& translation)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    iterToWord->second.secondaryTranslation = translation;
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

void nikitov::Dictionary::deletePrimaryTranslation(const std::string& word)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    if (iterToWord->second.secondaryTranslation.empty())
    {
      deleteAntonym(word);
      data_.erase(iterToWord);
    }
    else
    {
      std::swap(iterToWord->second.primaryTranslation, iterToWord->second.secondaryTranslation);
      iterToWord->second.secondaryTranslation = {};
    }
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

void nikitov::Dictionary::deleteSecondaryTranslation(const std::string& word)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    if (iterToWord->second.secondaryTranslation.empty())
    {
      throw std::logic_error("<ERROR: NOTHING TO DO>");
    }
    else
    {
      iterToWord->second.secondaryTranslation = {};
    }
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

void nikitov::Dictionary::addAntonym(const std::string& word, const std::string& antonym)
{
  auto iterToWord = data_.find(word);
  auto iterToAntonym = data_.find(antonym);
  if (iterToWord != data_.end() && iterToAntonym != data_.end())
  {
    if (iterToWord->second.antonym.empty() && iterToAntonym->second.antonym.empty())
    {
      iterToWord->second.antonym = antonym;
      iterToAntonym->second.antonym = word;
    }
    else
    {
      throw std::logic_error("<ERROR: ANTONYM ALREADY EXIST>");
    }
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

void nikitov::Dictionary::deleteAntonym(const std::string& word)
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    auto iterToAntonym = data_.find(iterToWord->second.antonym);
    iterToWord->second.antonym = {};
    if (iterToAntonym != data_.end() && iterToAntonym->second.antonym == word)
    {
      iterToAntonym->second.antonym = {};
    }
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

std::string nikitov::Dictionary::findWord(const std::string& word) const
{
  auto iterToWord = data_.find(word);
  std::string result;
  if (iterToWord != data_.end())
  {
    result += word;
    result += " - ";
    result += iterToWord->second.primaryTranslation;
    if (!iterToWord->second.secondaryTranslation.empty())
    {
      result += ", ";
      result += iterToWord->second.secondaryTranslation;
    }
    if (!iterToWord->second.antonym.empty())
    {
      result += " (";
      result += iterToWord->second.antonym;
      result += ')';
    }
    result += ';';
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
  return result;
}

std::string nikitov::Dictionary::findAntonym(const std::string& word) const
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    return findWord(iterToWord->second.antonym);
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

std::string nikitov::Dictionary::findTranslation(const std::string& word) const
{
  auto iterToWord = data_.find(word);
  if (iterToWord != data_.end())
  {
    return iterToWord->second.primaryTranslation;
  }
  else
  {
    throw std::logic_error("<ERROR: NO MATCHES>");
  }
}

std::istream& nikitov::operator>>(std::istream& input, Dictionary& dict)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }

  while (input)
  {
    std::string word;
    detail::Word translation;
    input >> word >> DelimiterChar({ '-' }) >> translation;
    if (input)
    {
      dict.data_.insert({ word, translation });
    }
    else if (!input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return input;
}

std::ostream& nikitov::operator<<(std::ostream& output, const Dictionary& dict)
{
  std::vector< std::string > words;
  auto getFirst = static_cast< const std::string& (*)(const std::pair< std::string, detail::Word >&) >(std::get< 0 >);
  std::transform(dict.data_.cbegin(), dict.data_.cend(), std::back_inserter(words), getFirst);

  std::vector< std::string > translations;
  std::transform(words.cbegin(), words.cend(), std::back_inserter(translations), std::bind(&Dictionary::findWord, dict,
    std::placeholders::_1));
  std::transform(translations.cbegin(), translations.cend(), translations.begin(), std::bind(std::plus< std::string >(),
    std::placeholders::_1, "\n"));
  std::copy(translations.cbegin(), translations.cend(), std::ostream_iterator< std::string >(output));
  return output;
}
