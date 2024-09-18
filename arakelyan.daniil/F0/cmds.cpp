#include "cmds.hpp"
#include <algorithm>
#include <functional>
#include <istream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <sys/_types/_key_t.h>
#include <utility>
#include <vector>

void arakelyan::addDictionary(std::istream &in, std::map< std::string, std::map< std::string, std::vector< std::string > > > &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) != dictionaries.end())
  {
    throw std::logic_error("<DICTIONARY ALREADY EXIST>");
  }
  std::map< std::string, std::vector< std::string > > newDictionary;
  dictionaries[name] = newDictionary;
}

void arakelyan::deleteDictionary(std::istream &in, std::map< std::string, std::map< std::string, std::vector< std::string > > > &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }
  dictionaries.erase(name);
}

void arakelyan::addWord(std::istream &in, std::map< std::string, std::map< std::string, std::vector< std::string > > > &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }

  auto &userDict = dictionaries[name];
  std::string word = "";
  std::string translate = "";
  in >> word >> translate;
  if (userDict.find(word) != userDict.end())
  {
    auto status = std::find(userDict[word].begin(), userDict[word].end(), translate);
    if (status != userDict[word].end())
    {
      throw std::logic_error("<THIS TRANSLATION FOR THIS WORD ALREADY EXISTS>");
    }
  }
  userDict[word].push_back(translate);
}

void arakelyan::removeWord(std::istream &in, std::map< std::string, std::map< std::string, std::vector< std::string > > > &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }
  auto &userDict = dictionaries[name];
  std::string word = "";
  in >> word;
  if (userDict.find(name) == userDict.end())
  {
    throw std::logic_error("<THAT WORD ISN'T IN THE DICTIONARY>");
  }
  userDict.erase(word);
}

void arakelyan::wordTranslations(std::ostream &out, std::istream &in,  const std::map< std::string, std::map< std::string, std::vector< std::string > > > &dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH THIS NAME>");
  }
  auto &userDict = dictionaries.at(name);
  std::string word = "";
  in >> word;
  if (userDict.find(word) == userDict.end())
  {
    throw std::logic_error("<THERE ARE NO WORD IN YOUR DICTIONARY>");
  }
  const auto translations = userDict.at(word);
  if (translations.empty())
  {
    throw std::logic_error("<THERE ARE NO TRANSLATIONS FOR THIS WORD>");
  }
  std::copy(translations.begin(), translations.end(), std::ostream_iterator< std::string >(out, " "));
  out << "\n";
}

void merge(std::map< std::string, std::vector< std::string > > &base, const std::pair< const std::string, std::vector< std::string > > &toMerge)
{
  const std::string &word = toMerge.first;
  const std::vector< std::string > &translations = toMerge.second;
  if (base.find(word) != base.end())
  {
    base[word].insert(base[word].end(), translations.begin(), translations.end());
  }
  else
  {
    base[word] = translations;
  }
}

void arakelyan::mergeDictionaries(std::istream &in, std::map< std::string, std::map< std::string, std::vector< std::string > > > &dictionaries)
{
  std::string name1 = "";
  std::string name2 = "";
  in >> name1 >> name2;
  if ((dictionaries.find(name1) == dictionaries.end()) || (dictionaries.find(name2) == dictionaries.end()))
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH ONE OF THOSE NAMES>");
  }
  std::map< std::string, std::vector< std::string > > res;
  auto &dictOne = dictionaries[name1];
  const auto &dictTwo = dictionaries[name2];
  auto func = std::bind(merge, std::ref(dictOne), std::placeholders::_1);
  std::for_each(dictTwo.cbegin(), dictTwo.cend(), func);
  dictionaries.erase(name2);
}

void arakelyan::moveWords(std::istream &in, std::map<std::string, std::map<std::string, std::vector<std::string>>> &dictionaries)
{
  std::string dictOneName = "";
  std::string word = "";
  std::string dictTwoName = "";
  in >> dictOneName >> word >> dictTwoName;
  if ((dictionaries.find(dictOneName) == dictionaries.end()) || (dictionaries.find(dictTwoName) == dictionaries.end()))
  {
    throw std::logic_error("<THERE ARE NO DICTIONARY WITH ONE OF THOSE NAMES>");
  }
  auto &dictOne = dictionaries[dictOneName];
  auto &dictTwo = dictionaries[dictTwoName];
  if (dictOne.find(word) == dictOne.end())
  {
    dictOne[word] = dictTwo.find(word)->second;
  }
  else
  {
    dictOne[word].insert(dictOne[word].end(), dictTwo[word].begin(), dictTwo[word].end());
  }
}

// void showWordAndTr(std::ostream &out, std::pair< std::string, std::vector< std::string > > &wordEntry)
// {
//   const std::string &word = wordEntry.first;
//   const std::vector< std::string > &translations = wordEntry.second;
//
//   out << "  Word: " << word << " -> Translations: ";
//
//   if (!translations.empty())
//   {
//     std::copy(translations.begin(), translations.end(), std::ostream_iterator< std::string >(out, " "));
//   }
//
//   out << '\n';
// }

struct ShowWord
{
  void operator()(std::ostream&, std::pair< std::string, std::vector< std::string > > &words);
};

void ShowWord::operator()(std::ostream &out, std::pair< std::string, std::vector< std::string > > &wordEntry)
{
  const std::string &word = wordEntry.first;
  const std::vector< std::string > &translations = wordEntry.second;

  out << "  Word: " << word << " -> Translations: ";

  if (!translations.empty())
  {
    std::copy(translations.begin(), translations.end(), std::ostream_iterator< std::string >(out, " "));
  }

  out << '\n';
}

void showName(std::ostream &out, const std::pair< std::string, std::map< std::string, std::vector< std::string > > > &dict)
{
  std::string name = dict.first;
  out << "Dictionary: " << name << '\n';
  // auto showWordFunc = std::bind(showWordAndTr, std::ref(out), std::placeholders::_1);
  ShowWord showWordFunc;
  std::for_each(dict.second.begin(), dict.second.end(), std::bind(showWordFunc, std::ref(out), std::placeholders::_1));
  out << '\n';
}

void arakelyan::showAllDictionaries(std::ostream &out, std::istream&, const std::map<std::string, std::map<std::string, std::vector<std::string>>> &dictionaries)
{
  auto showFunc = std::bind(showName, std::ref(out), std::placeholders::_1);
  std::for_each(dictionaries.begin(), dictionaries.end(), showFunc);
}
