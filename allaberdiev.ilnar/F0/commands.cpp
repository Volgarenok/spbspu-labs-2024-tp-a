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

void allaberdiev::translateWord(std::ostream& out, std::istream& in, const std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  std::string englishWord = "";
  in >> name >> englishWord;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  const std::map< std::string, std::vector< std::string > >& neededDict = dicts.at(name);

  if (neededDict.find(englishWord) == neededDict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  const std::vector< std::string > translations = neededDict.at(englishWord);
  out << englishWord << " ";
  std::copy(translations.cbegin(), translations.cend(), std::ostream_iterator< std::string >(out, " "));
  out << "\n";
  return;
}

void mergeEntry(std::map< std::string, std::vector< std::string > >& first, const std::pair< const std::string, std::vector< std::string > >& entry)
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

void allaberdiev::mergeDict(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string firstName = "";
  std::string secondName = "";
  std::map< std::string, std::vector< std::string > > result = {};
  in >> firstName >> secondName;
  if (dicts.find(firstName) == dicts.end() || dicts.find(secondName) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }
  std::map< std::string, std::vector< std::string > >& firstDict = dicts[firstName];
  const std::map< std::string, std::vector< std::string > >& secondDict = dicts[secondName];
  std::for_each(secondDict.cbegin(), secondDict.cend(), std::bind(mergeEntry, std::ref(firstDict), std::placeholders::_1));
}

bool notKeysInMap(const std::map< std::string, std::vector< std::string > >& map, const std::string& key)
{
  return map.find(key) == map.end();
}

void allaberdiev::combineDict(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string newName, firstName, secondName;
  in >> newName >> firstName >> secondName;
  if (dicts.find(firstName) == dicts.end() || dicts.find(secondName) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& firstDict = dicts[firstName];
  const std::map< std::string, std::vector< std::string > >& secondDict = dicts[secondName];
  std::map< std::string, std::vector< std::string > > resultDict = {};
  auto pred = std::bind(notKeysInMap, std::cref(resultDict), std::placeholders::_1);
  std::copy(firstDict.begin(), firstDict.end(), std::inserter(resultDict, resultDict.end()));
  std::copy_if(secondDict.begin(), secondDict.end(), std::inserter(resultDict, resultDict.end()),
      [&pred](const auto& entry) {
        return pred(entry.first);
      });

  dicts[newName] = resultDict;
}
