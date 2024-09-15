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

void altun::merge(std::istream& in,
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
  std::map< std::string, std::vector< std::string > >& firstDict = dicts[first];
  const std::map< std::string, std::vector< std::string > >& secondDict = dicts[second];
  std::for_each(secondDict.cbegin(), secondDict.cend(), std::bind(mergeEntry, std::ref(firstDict), std::placeholders::_1));
}

bool isCommonTranslation(const std::string& firstTranslation, const std::vector< std::string >& secondTranslations)
{
  return std::find(secondTranslations.begin(), secondTranslations.end(), firstTranslation) != secondTranslations.end();
}

void insertCommonTranslations(std::map< std::string, std::vector< std::string > >& result,
    const std::pair< const std::string, std::vector< std::string > >& entry,
    const std::map< std::string, std::vector< std::string > >& secondDict)
{
  const std::string& word = entry.first;
  const std::vector< std::string >& firstTranslations = entry.second;

  auto it2 = secondDict.find(word);
  if (it2 != secondDict.end())
  {
    const std::vector< std::string >& secondTranslations = it2->second;
    std::vector< std::string > common;
    std::copy_if(firstTranslations.begin(), firstTranslations.end(), std::back_inserter(common),
        std::bind(isCommonTranslation, std::placeholders::_1, std::cref(secondTranslations)));
    if (!common.empty())
    {
      result[word] = common;
    }
  }
}

void altun::intersection(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string first = "";
  std::string second = "";
  in >> first >> second;

  if (dicts.find(first) == dicts.end() || dicts.find(second) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& firstDict = dicts[first];
  const std::map< std::string, std::vector< std::string > >& secondDict = dicts[second];
  std::map< std::string, std::vector< std::string > > result = {};
  using namespace std::placeholders;
  std::for_each(firstDict.begin(), firstDict.end(),
      std::bind(insertCommonTranslations, std::ref(result), _1, std::cref(secondDict)));

  if (result.empty()) {
    std::cout << "<NO INTERSECTION>\n";
  } else {
    std::for_each(result.begin(), result.end(), [](const std::pair<const std::string, std::vector<std::string>>& pair) {
        const auto& translations = pair.second;
        for (const auto& translation : translations) {
            std::cout << translation << std::endl;
        }
    });
  }
}

bool keyNotInMap(const std::map< std::string, std::vector< std::string > >& map, const std::string& key)
{
  return map.find(key) == map.end();
}

void altun::combining(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string first = "";
  std::string second = "";
  in >> first >> second;
  if (dicts.find(first) == dicts.end() || dicts.find(second) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& firstDict = dicts[first];
  const std::map< std::string, std::vector< std::string > >& secondDict = dicts[second];
  std::map< std::string, std::vector< std::string > > result = {};
  auto pred = std::bind(keyNotInMap, std::cref(result), std::placeholders::_1);
  std::copy(firstDict.begin(), firstDict.end(), std::inserter(result, result.end()));
  std::copy_if(secondDict.begin(), secondDict.end(), std::inserter(result, result.end()),
      [&pred](const auto& entry) {
        return pred(entry.first);
      });

  if (result.empty()) {
    std::cout << "<EMPTY>\n";
  } else {
    std::for_each(result.begin(), result.end(), [](const std::pair<const std::string, std::vector<std::string>>& pair) {
        const auto& translations = pair.second;
        for (const auto& translation : translations) {
            std::cout << translation << std::endl;
        }
    });
  }
}

std::vector< std::string > computeDifference(const std::vector< std::string >& v1, const std::vector< std::string >& v2)
{
  std::vector< std::string > difference;
  std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(difference));
  return difference;
}

void handleTranslationComparison(const std::map< std::string, std::vector< std::string > >& firstDict,
    const std::map< std::string, std::vector< std::string > >& secondDict,
    std::map< std::string, std::vector< std::string > >& result)
{
  std::for_each(firstDict.begin(), firstDict.end(), [&](const auto& pair) {
    auto second_it = secondDict.find(pair.first);
    if (second_it != secondDict.end())
    {
      const auto& second_translations = second_it->second;
      std::vector< std::string > diff = computeDifference(pair.second, second_translations);
      if (!diff.empty())
      {
        result[pair.first] = diff;
      }
    }
    else
    {
      result[pair.first] = pair.second;
    }
  });
}

void altun::difference(std::istream& in,
    std::map< std::string, std::map< std::string, std::vector< std::string > > >& dicts)
{
  std::string first = "";
  std::string second = "";
    in >> first >> second;

  if (dicts.find(first) == dicts.end() || dicts.find(second) == dicts.end())
  {
    throw std::logic_error("<DICTIONARY NOT FOUND>");
  }

  const std::map< std::string, std::vector< std::string > >& firstDict = dicts[first];
  const std::map< std::string, std::vector< std::string > >& secondDict = dicts[second];
  std::map< std::string, std::vector< std::string > > result = {};

  std::set_difference(firstDict.begin(), firstDict.end(), secondDict.begin(), secondDict.end(),
      std::inserter(result, result.end()),
      [](const auto& lhs, const auto& rhs) {
        return lhs.first < rhs.first;
      });

  if (result.empty()) handleTranslationComparison(firstDict, secondDict, result);

  if (result.empty()) {
        std::cout << "<EQUAL DICTIONARIES>\n";
    } else {
        std::for_each(result.begin(), result.end(), [](const std::pair<const std::string, std::vector<std::string>>& pair) {
            const auto& translations = pair.second;
            for (const auto& translation : translations) {
                std::cout << pair.first << " " << translation << std::endl;
            }
        });
    }
}
