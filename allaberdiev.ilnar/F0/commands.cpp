#include "commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>

void allaberdiev::createDict(std::istream& in, std::map< std::string, std::map < std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;

  if (dicts.find(name) != dicts.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }

  std::map< std::string, std::vector< std::string > > newDict = {};
  dicts[name] = newDict;
}

void allaberdiev::deleteDict(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  dicts.erase(name);
}

void allaberdiev::addWord(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& neededDict = dicts[name];
  std::string word = "";
  std::string translation = "";
  in >> word >> translation;
  neededDict[word].push_back(translation);
}

void allaberdiev::removeWord(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& neededDict = dicts[name];
  std::string word = "";
  in >> word;
  if (neededDict.find(word) == neededDict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  neededDict.erase(word);
}

void allaberdiev::translateWord(std::ostream& out, std::istream& in, const std::map< std::string, std::map< std::string, std::vector< std::string > > >& dictionaries)
{
  std::string name = "";
  std::string englishWord = "";
  in >> name >> englishWord;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  const std::map< std::string, std::vector< std::string > >& needed_dict = dictionaries.at(name);

  if (needed_dict.find(englishWord) == needed_dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  const std::vector< std::string > translations = needed_dict.at(englishWord);
  out << englishWord << " ";
  std::copy(translations.cbegin(), translations.cend(), std::ostream_iterator< std::string >(out, " "));
  out << "\n";
  return;
}