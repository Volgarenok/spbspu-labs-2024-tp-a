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
    throw std::logic_error("<DICTIONARY NOT FOUND>");
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

void allaberdiev::translateWord(std::ostream& out, std::istream& in,
    const std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string name = "";
  std::string englishWord = "";
  in >> name >> englishWord;
  if (dicts.find(name) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
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

std::vector< std::string > computeDiff(const std::vector< std::string >& v1, const std::vector< std::string >& v2)
{
  std::vector< std::string > difference;
  std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(difference));
  return difference;
}

void handleTranslationComparison(const std::map< std::string, std::vector< std::string > >& firstDict,
    const std::map< std::string, std::vector< std::string > >& secondDict, std::map< std::string, std::vector< std::string > >& resultDict)
{
  std::for_each(firstDict.begin(), firstDict.end(), [&](const auto& pair) {
    auto second_it = secondDict.find(pair.first);
    if (second_it != secondDict.end())
    {
      const auto& second_translations = second_it->second;
      std::vector< std::string > diff = computeDiff(pair.second, second_translations);
      if (!diff.empty())
      {
        resultDict[pair.first] = diff;
      }
    }
    else
    {
      resultDict[pair.first] = pair.second;
    }
  });
}

void allaberdiev::diffDict(std::istream& in, std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string newName = "";
  std::string firstName = "";
  std::string secondName = "";
  std::string comparisonType = "";
  in >> newName >> firstName >> secondName >> comparisonType;

  if (dicts.find(firstName) == dicts.end() || dicts.find(secondName) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& firstDict = dicts[firstName];
  const std::map< std::string, std::vector< std::string > >& secondDict = dicts[secondName];
  std::map< std::string, std::vector< std::string > > resultDict = {};

  if (comparisonType == "translation")
  {
    handleTranslationComparison(firstDict, secondDict, resultDict);
  }
  else
  {
    std::set_difference(firstDict.begin(), firstDict.end(), secondDict.begin(), secondDict.end(),
        std::inserter(resultDict, resultDict.end()),
        [](const auto& lhs, const auto& rhs) {
          return lhs.first < rhs.first;
        });
  }
  dicts[newName] = resultDict;
}
