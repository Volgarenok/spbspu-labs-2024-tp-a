#include "cmds.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
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
