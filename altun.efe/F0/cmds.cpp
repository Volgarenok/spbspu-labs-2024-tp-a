#include "cmds.hpp"
#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>

void altun::createDictionary(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
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

void altun::deleteDictionary(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  dicts.erase(name);
}

void altun::addWord(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& wantedDict = dicts[name];
  std::string word = "";
  std::string translation = "";
  in >> word >> translation;
  wantedDict[word].push_back(translation);
}

void altun::removeWord(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  in >> name;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& wantedDict = dicts[name];
  std::string word = "";
  in >> word;
  if (wantedDict.find(word) == wantedDict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  wantedDict.erase(word);
}

void altun::translateWord(std::ostream& out,
    std::istream& in,
    const std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  std::string engWord = "";
  in >> name >> engWord;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  const std::map< std::string, std::vector< std::string > >& wantedDict = dicts.at(name);

  if (wantedDict.find(engWord) == wantedDict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  const std::vector< std::string > translations = wantedDict.at(engWord);
  out << engWord << " ";
  std::copy(translations.cbegin(), translations.cend(), std::ostream_iterator< std::string >(out, " "));
  out << "\n";
  return;
}

void mergeEntry(std::map< std::string, std::vector< std::string > >& first,
    const std::pair< const std::string, std::vector< std::string > >& entry)
{
  const std::string& key = entry.first;
  const std::vector< std::string >& values = entry.second;

  if (first.find(key) != first.end())
  {
    first[key].insert(first[key].end(), values.begin(), values.end());
  }
  else
  {
    first[key] = values;
  }
}

void altun::mergeDictionaries(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string first = "";
  std::string second = "";
  std::map< std::string, std::vector< std::string > > result = {};
  in >> first >> second;
  if (dicts.find(first) == dicts.end() || dicts.find(second) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& first = dicts[first];
  const std::map< std::string, std::vector< std::string > >& second = dicts[second];
  std::for_each(second.cbegin(), second.cend(), std::bind(mergeEntry, std::ref(first), std::placeholders::_1));
}
