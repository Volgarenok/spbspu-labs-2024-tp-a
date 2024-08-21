#include "ERDictionary.hpp"
#include <algorithm>
#include <locale>
#include <iterator>
#include <functional>
#include <numeric>
#include <fstream>

bool kozakova::ERDictionary::insert(const std::string& word, const std::string& trans)
{
  return dictionary[word].insert(trans).second;
}

const std::set< std::string >* kozakova::ERDictionary::search(const std::string& word) const
{
  auto result = dictionary.find(word);
  if (result == dictionary.end())
  {
    return nullptr;
  }
  return &(*result).second;
}

bool kozakova::ERDictionary::remove(const std::string& word)
{
  return dictionary.erase(word);
}

bool kozakova::ERDictionary::removeTrans(const std::string& word, const std::string& trans)
{
  bool result = dictionary[word].erase(trans);
  if (dictionary[word].empty())
  {
    dictionary.erase(word);
  }
  return result;
}

bool kozakova::isShortTrans(const std::string& trans1, const std::string& trans2)
{
  return trans1.size() < trans2.size();
}

std::string kozakova::ERDictionary::searchShort(const std::string& word) const
{
  return *std::min_element(dictionary.at(word).begin(), dictionary.at(word).end(), isShortTrans);
}

std::set< std::string > kozakova::ERDictionary::searchSame(const std::string& word1, const std::string& word2) const
{
  std::set< std::string > inter;
  std::set_intersection(dictionary.at(word1).begin(), dictionary.at(word1).end(),
    dictionary.at(word2).begin(), dictionary.at(word2).end(), std::inserter(inter, inter.end()));
  return inter;
}

bool kozakova::inDict(const ERDictionary& dict, const std::pair< std::string, std::set< std::string > >& el)
{
  auto result = dict.dictionary.find(el.first);
  if (result == dict.dictionary.end())
  {
    return false;
  }
  return true;
}

bool kozakova::ERDictionary::operator==(const ERDictionary& dict) const
{
  using namespace std::placeholders;
  return dictionary.size() == dict.dictionary.size() &&
    std::all_of(dictionary.begin(), dictionary.end(), std::bind(inDict, dict, _1));
}

struct combineTrans
{
  void operator()(std::pair< const std::string, std::set< std::string > >& el)
  {
    el.second.insert(dict[el.first].begin(), dict[el.first].end());
  }
  std::unordered_map< std::string, std::set< std::string > > dict;
};

void kozakova::ERDictionary::combine(const ERDictionary& dict)
{
  std::for_each(dictionary.begin(), dictionary.end(), combineTrans{ dict.dictionary });
}

struct intersectDicts
{
  std::unordered_map< std::string, std::set< std::string > > operator()(const kozakova::ERDictionary& dict,
    const std::pair< std::string, std::set< std::string > >& el)
  {
    if (kozakova::inDict(dict, el))
    {
      std::set< std::string > inter;
      std::set_intersection(dict.dictionary.at(el.first).begin(), dict.dictionary.at(el.first).end(),
        el.second.begin(), el.second.end(), std::inserter(inter, inter.end()));
      newDict[el.first] = inter;
    }
    return newDict;
  }
  std::unordered_map< std::string, std::set< std::string > > newDict;
};

std::unordered_map< std::string, std::set< std::string > > kozakova::intersect(const ERDictionary& dict1, const ERDictionary& dict2)
{
  intersectDicts newDictionary;
  using namespace std::placeholders;
  std::for_each(dict1.dictionary.begin(), dict1.dictionary.end(), std::bind(std::ref(newDictionary), dict2, _1));
  return newDictionary.newDict;
}

std::istream& kozakova::operator>>(std::istream& in, ERDictionary& dict)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string word;
  std::string trans;
  in >> word >> trans;
  if (isWord(word) && isTrans(trans))
  {
    dict.dictionary[word].insert(trans);
  }
  return in;
}

void kozakova::print(std::ofstream& out, const std::pair< const std::string, ERDictionary >& el)
{
  using namespace std::placeholders;
  std::for_each(el.second.dictionary.begin(), el.second.dictionary.end(), std::bind(printPair, std::ref(out), el.first, _1));
}

void kozakova::printPair(std::ofstream& out, const std::string& nameDict, const std::pair< std::string, std::set< std::string > >& el)
{
  using namespace std::placeholders;
  std::for_each(el.second.begin(), el.second.end(), std::bind(printWord, std::ref(out), nameDict, el.first, _1));
}

void kozakova::printWord(std::ofstream& out, const std::string& nameDict, const std::string& word, const std::string& el)
{
  out << nameDict << " " << word << " " << el << "\n";
}

bool kozakova::isEnglish(const char& c)
{
  return std::isalpha(c);
}

bool kozakova::isRussian(const char& c)
{
  std::locale loc("RUSSIAN");
  return std::isalpha(c, loc) && !std::isalpha(c);
}

bool kozakova::isWord(const std::string& word)
{
  auto result{ std::find_if_not(word.begin(), word.end(), isEnglish) };
  if (result == word.end())
  {
    return true;
  }
  return false;
}

bool kozakova::isTrans(const std::string& word)
{
  auto result{ std::find_if_not(word.begin(), word.end(), isRussian) };
  if (result == word.end())
  {
    return true;
  }
  return false;
}
