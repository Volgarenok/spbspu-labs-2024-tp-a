#include "eng-rusDictionary.hpp"

#include <algorithm>
#include <functional>

belokurskaya::EngRusDict::EngRusDict()
{}

belokurskaya::EngRusDict::EngRusDict(const EngRusDict& other)
{
  words_ = other.words_;
}

belokurskaya::EngRusDict::EngRusDict(EngRusDict&& other) noexcept:
  words_(std::move(other.words_))
{
  other.clear();
}

belokurskaya::EngRusDict::~EngRusDict()
{
  clear();
}

void belokurskaya::EngRusDict::clear()
{
  words_.clear();
}

std::set< std::string > belokurskaya::EngRusDict::getTranslations(const std::string& eng) const
{
  return words_.at(eng);
}

size_t belokurskaya::EngRusDict::getCountWords() const
{
  return words_.size();
}

size_t belokurskaya::EngRusDict::getCountTranslations(const std::string& eng) const
{
  return words_.at(eng).size();
}

void belokurskaya::EngRusDict::display(std::ostream& out) const
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    for (const std::pair< std::string, std::set< std::string > >& pair : words_)
    {
      out << "\n" << pair.first << ": ";
      if (!pair.second.empty())
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

void belokurskaya::EngRusDict::addTranslation(const std::string& eng, const std::string& translation)
{
  words_[eng].insert(getLettersToLower(translation));
}

void belokurskaya::EngRusDict::removeTranslation(const std::string& eng, const std::string& translation)
{
  words_[eng].erase(words_.at(eng).find(getLettersToLower(translation)));
}

void belokurskaya::EngRusDict::addWord(const std::string& eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("Invalid argument");
  }
  words_[getLettersToLower(eng)] = std::set< std::string >();
}

void belokurskaya::EngRusDict::removeWord(const std::string& eng)
{
  words_.erase(eng);
}

bool belokurskaya::EngRusDict::containsWord(const std::string& word) const
{
  return words_.find(word) != words_.end();
}

bool belokurskaya::EngRusDict::containsTranslation(const std::string& eng, const std::string& translation) const
{
  auto it = words_.find(eng);
  if (it != words_.end())
  {
    return (it->second.find(translation) != it->second.end());
  }
  return false;
}

std::set< std::string > belokurskaya::EngRusDict::getWords() const
{
  std::set< std::string > allWords;
  for (const auto& pair : words_)
  {
    allWords.insert(pair.first);
  }
  return allWords;
}

void belokurskaya::EngRusDict::addWordFromEngRusDict(const EngRusDict& other)
{
  for (const std::pair< std::string, std::set< std::string > >& pair : other.words_)
  {
    try
    {
      words_.at(pair.first).insert(pair.second.begin(), pair.second.end());
    }
    catch (const std::out_of_range&)
    {
      words_.insert(pair);
    }
  }
}

void belokurskaya::EngRusDict::removeWordFromEngRusDict(const EngRusDict& other)
{
  for (const std::pair< std::string, std::set< std::string > >& pair : other.words_)
  {
    try
    {
      words_.at(pair.first).erase(pair.second.begin(), pair.second.end());
    }
    catch (const std::out_of_range&)
    {
      continue;
    }
  }
}

belokurskaya::EngRusDict& belokurskaya::EngRusDict::operator=(const belokurskaya::EngRusDict& other)
{
  words_ = other.words_;
  return *this;
}

std::string belokurskaya::EngRusDict::getLettersToLower(std::string word)
{
  using namespace std::placeholders;
  std::transform(word.begin(), word.end(), word.begin(), std::ptr_fun< int, int >(std::tolower));
  return word;
}

bool belokurskaya::EngRusDict::containsOnlyEnglishLetters(const std::string& word) const
{
  bool result = true;
  for (const char& c : word)
  {
    if (!std::isalpha(c))
    {
      result = false;
      break;
    }
  }
  return result;
}

belokurskaya::EngRusDict belokurskaya::getIntersectionWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict newDict;
  for (const std::pair< std::string, std::set< std::string > >& pair : erd2.words_)
  {
    if (erd1.words_.find(pair.first) != erd1.words_.end())
    {
      newDict.words_[pair.first];
      const std::set<std::string>& translations = erd1.words_.at(pair.first);
      newDict.words_.at(pair.first).insert(translations.begin(), translations.end());
    }
  }
  return newDict;
}

belokurskaya::EngRusDict belokurskaya::getDifferenceWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict newDict;
  for (const std::pair< std::string, std::set< std::string > >& pair : erd2.words_)
  {
    if (erd1.words_.find(pair.first) == erd1.words_.end())
    {
      newDict.words_[pair.first] = pair.second;
    }
  }
  for (const std::pair< std::string, std::set< std::string > >& pair : erd1.words_)
  {
    if (erd2.words_.find(pair.first) == erd2.words_.end())
    {
      newDict.words_[pair.first] = pair.second;
    }
  }
  return newDict;
}
