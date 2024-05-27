#include "eng-rusDictionary.hpp"

#include <algorithm>

belokurskaya::EngRusDict::EngRusDict()
{
  name_ = "";
}

belokurskaya::EngRusDict::EngRusDict(const std::string& name):
  name_(name)
{}

belokurskaya::EngRusDict::EngRusDict(const EngRusDict& other)
{
  name_ = other.name_;
  words_ = other.words_;
}

belokurskaya::EngRusDict::~EngRusDict()
{}

void belokurskaya::EngRusDict::clear()
{
  name_.clear();
  words_.clear();
}

std::string belokurskaya::EngRusDict::getName() const
{
  return name_;
}

std::set< std::string > belokurskaya::EngRusDict::getTranslations(std::string eng)
{
  return words_[eng];
}

size_t belokurskaya::EngRusDict::getCountWords()
{
  return words_.size();
}

size_t belokurskaya::EngRusDict::getCountTranslations(std::string eng)
{
  return words_[eng].size();
}

void belokurskaya::EngRusDict::addTranslation(std::string eng, std::string translation)
{
  if (!containsOnlyRussianLetters(translation))
  {
    throw std::invalid_argument("");
  }
  words_[eng].insert(getLettersToLower(translation));
}

void belokurskaya::EngRusDict::removeTranslation(std::string eng, std::string translation)
{
  if (!containsOnlyRussianLetters(translation))
  {
    throw std::invalid_argument("");
  }
  words_[eng].erase(std::find(words_[eng].begin(), words_[eng].end(), getLettersToLower(translation)));
}

void belokurskaya::EngRusDict::addWord(std::string eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("");
  }
  std::set< std::string > translations;
  words_[getLettersToLower(eng)] = translations;
}

void belokurskaya::EngRusDict::removeWord(std::string eng)
{
  words_.erase(eng);
}

void belokurskaya::EngRusDict::addWordFromEngRusDict(EngRusDict& other)
{
  for (const std::pair< std::string, std::set< std::string > > pair : other.words_)
  {
    words_.insert(pair);
  }
}

void belokurskaya::EngRusDict::removeWordFromEngRusDict(EngRusDict& other)
{
  for (const std::pair< std::string, std::set< std::string > > pair : other.words_)
  {
    if (words_.find(pair.first) != words_.cend())
    {
      for (std::string translation : pair.second)
      {
        words_[pair.first].erase(std::find(words_[pair.first].begin(), words_[pair.first].end(), translation));
      }
      if (words_[pair.first].size() == 0)
      {
        words_.erase(pair.first);
      }
    }
  }
}

void belokurskaya::EngRusDict::display(std::ostream& out) const
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << name_;
    for (const auto& pair : words_)
    {
      out << "\n" << pair.first << ": ";
      f(!pair.second.empty())
      {
        auto it = pair.second.begin();
        out << *it;
        ++it;
        for (; it != pair.second.end(); ++it)
        {
          out << ", " << *it;
        }
      }
    }
    out << "\n";
  }
}

belokurskaya::EngRusDict& belokurskaya::EngRusDict::operator=(const belokurskaya::EngRusDict& other)
{
  name_ = other.name_;
  words_ = other.words_;
  return *this;
}

std::string belokurskaya::EngRusDict::getLettersToLower(const std::string& word)
{
  std::string result;
  for (char c : word)
  {
    result += std::tolower(c);
  }
  return result;
}

bool belokurskaya::EngRusDict::containsOnlyRussianLetters(const std::string& word) const
{
  bool result = true;
  for (char c : word)
  {
    if (!(c >= 'à' && c <= 'ÿ' || c >= 'À' && c <= 'ß'))
    {
      result = false;
      break;
    }
  }
  return result;
}

bool belokurskaya::EngRusDict::containsOnlyEnglishLetters(const std::string& word) const
{
  bool result = true;
  for (char c : word)
  {
    if (!(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))
    {
      result = false;
      break;
    }
  }
  return result;
}

belokurskaya::EngRusDict belokurskaya::getIntersectionWithEngRusDict(std::string name, EngRusDict& erd1, EngRusDict& erd2)
{
  EngRusDict newDict(name);
  for (const std::pair< std::string, std::set< std::string > > pair : erd2.words_)
  {
    if (erd1.words_.find(pair.first) != erd1.words_.cend())
    {
      newDict.addWord(pair.first);
      for (std::string translation : pair.second)
      {
        if (std::find(erd1.words_[pair.first].begin(), erd1.words_[pair.first].end(), translation) != erd1.words_[pair.first].end())
        {
          newDict.addTranslation(pair.first, translation);
        }
      }
    }
  }
  return newDict;
}

belokurskaya::EngRusDict belokurskaya::getDifferenceWithEngRusDict(std::string name,
  belokurskaya::EngRusDict& erd1, belokurskaya::EngRusDict& erd2)
{
  EngRusDict newDict(name);
  for (const std::pair< std::string, std::set< std::string > > pair : erd2.words_)
  {
    if (erd1.words_.find(pair.first) == erd1.words_.end())
    {
      newDict.words_[pair.first] = pair.second;
    }
  }
  for (const std::pair< std::string, std::set< std::string > > pair : erd1.words_)
  {
    if (erd2.words_.find(pair.first) == erd2.words_.end())
    {
      newDict.words_[pair.first] = pair.second;
    }
  }
  return newDict;
}
