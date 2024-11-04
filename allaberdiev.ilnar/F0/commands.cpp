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