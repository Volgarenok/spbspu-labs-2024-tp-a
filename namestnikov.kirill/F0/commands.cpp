#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <utility>
#include <functional>
#include <vector>
#include <delimeters.hpp>

void namestnikov::doHelp(std::ostream & out)
{
  out << "Available commands:\n";
  out << "add <dict> <key> <translation> - add new word with translation to the dictionary\n";
  out << "find <dict> <key> - find a word by the key in dictionary\n";
  out << "remove <dict> <key> - remove a word by the key in the dictionary\n";
  out << "subtract <resdict> <dict1> <dict2> - make a dictionary with subtracting two dictionaries\n";
  out << "merge <resdict> <dict1> <dict2> - make a dictionary with all words from two dictionaries\n";
  out << "export <dict> <filename> - export a dictionary to file\n";
  out << "palindrome <dict> - find all words-palindroms in dictionary\n";
  out << "import <dict> <filename> - import a dictionary from file\n";
  out << "prefix <newdict> <dict> <prefix> - make a new dictionary with words that has this prefix\n";
  out << "postfix <newdict> <dict> <postfix> - make a new dictionary with words that has this postfix\n";
  out << "suffix <newdict> <dict> <suffix> - make a new dictionary with words that has this suffix\n";
}

bool startsWith(const std::pair< std::string, std::string > & pairDict, const std::string & sub)
{
  size_t strLength = pairDict.first.size();
  size_t subLength = sub.size();
  return ((strLength >= subLength) && (pairDict.first.compare(0, subLength, sub) == 0));
}

bool endsWith(const std::pair< std::string, std::string > & pairDict, const std::string & sub)
{
  size_t strLength = pairDict.first.size();
  size_t subLength = sub.size();
  return ((strLength >= subLength) && (pairDict.first.compare(strLength - subLength, subLength, sub) == 0));
}

void namestnikov::doCreate(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string newName = "";
  in >> newName;
  if (mainMap.find(newName) != mainMap.end())
  {
    out << "The dictionary with name " << newName << " already exists.\n";
    return;
  }
  std::unordered_map< std::string, std::string > newDict;
  mainMap[newName] = newDict;
  out << newName << " is successfully created.\n";
}

void namestnikov::doAdd(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string dictName = "";
  in >> dictName;
  std::string key = "";
  in >> key;
  std::string translation = "";
  in >> translation;
  if (mainMap.find(dictName) == mainMap.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  if (mainMap[dictName].find(key) != mainMap[dictName].end())
  {
    out << "The word " << key << " already exists in " << dictName << ".\n";
    return;
  }
  mainMap[dictName].insert(std::make_pair(key, translation));
}

void namestnikov::doFind(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string dictName = "";
  in >> dictName;
  std::string key = "";
  in >> key;
  if (mainMap.find(dictName) == mainMap.end())
  {
    out << "The dictionary with name " << dictName << " doesn't exist.\n";
    return;
  }
  if (mainMap[dictName].find(key) == mainMap[dictName].end())
  {
    out << "The word " << key << " doesn't exist in " << dictName << ".\n";
    return;
  }
  out << mainMap[dictName][key] << "\n";
}

void namestnikov::doRemove(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string dictName = "";
  in >> dictName;
  std::string key = "";
  in >> key;
  if (mainMap[dictName].find(key) == mainMap[dictName].end())
  {
    throw std::invalid_argument("The word doesn't exist in this dict");
  }
  mainMap[dictName].erase(mainMap[dictName].find(key));
  out << "The word " << key << " sucessfully deleted from " << dictName << ".\n";
}

bool isNotExist(const std::pair< std::string, std::string > & pairDict, const std::unordered_map< std::string, std::string > & map)
{
  return (map.find(pairDict.first) == map.end());
}

void namestnikov::doSubtract(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string resDict = "";
  in >> resDict;
  std::string firstDict = "";
  in >> firstDict;
  std::string secondDict = "";
  in >> secondDict;
  std::unordered_map< std::string, std::string > res;
  std::unordered_map< std::string, std::string > first = mainMap.at(firstDict);
  std::unordered_map< std::string, std::string > second = mainMap.at(secondDict);
  using namespace std::placeholders;
  auto notExist = std::bind(isNotExist, _1, second);
  std::copy_if(first.begin(), first.end(), std::inserter(res, res.end()), notExist);
  mainMap[resDict] = res;
  out << "Dictionary " << resDict << " is successfully created.\n";
}

void namestnikov::doMerge(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string resDict = "";
  in >> resDict;
  std::string firstDict = "";
  in >> firstDict;
  std::string secondDict = "";
  in >> secondDict;
  std::unordered_map< std::string, std::string > res;
  std::unordered_map< std::string, std::string > first = mainMap.at(firstDict);
  std::unordered_map< std::string, std::string > second = mainMap.at(secondDict);
  std::copy(first.begin(), first.end(), std::inserter(res, res.end()));
  using namespace std::placeholders;
  auto notExist = std::bind(isNotExist, _1, res);
  std::copy_if(second.begin(), second.end(), std::inserter(res, res.end()), notExist);
  mainMap[resDict] = res;
  out << "Dictionary " << resDict << " is successfully created.\n";
}

void namestnikov::doExport(std::istream & in, const dictMain & mainMap)
{
  std::string dict = "";
  in >> dict;
  std::string filename = "";
  in >> filename;
  if (!endsWith(std::make_pair(filename, dict), ".txt"))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::ofstream outFile(filename);
  if (!outFile.is_open())
  {
    throw std::invalid_argument("Can't open this file");
  }
  outFile << dict << "\n";
  std::unordered_map< std::string, std::string > res = mainMap.at(dict);
  for (const auto & pair: res)
  {
    outFile << pair.first << " - " << pair.second << "\n";
  }
}

void namestnikov::doImport(std::istream & in, dictMain & mainMap)
{
  std::string dict = "";
  in >> dict;
  std::string filename = "";
  in >> filename;
  if (!endsWith(std::make_pair(filename, dict), ".txt"))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::ifstream inFile(filename);
  if (!inFile.is_open())
  {
    throw std::invalid_argument("Can't open this file");
  }
  std::string resDict = "";
  inFile >> resDict;
  std::unordered_map< std::string, std::string > res;
  std::string key = "";
  std::string value = "";
  using delC = namestnikov::DelimeterChar;
  while (inFile >> key >> delC{'-'} >> value)
  {
    res.insert(std::make_pair(key, value));
  }
  mainMap[resDict] = res;
}

void namestnikov::doPrefix(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string newDict = "";
  in >> newDict;
  std::string dict = "";
  in >> dict;
  std::unordered_map< std::string, std::string > searchDict = mainMap.at(dict);
  if (searchDict.empty())
  {
    out << dict << " is empty.\n";
    return;
  }
  std::unordered_map< std::string, std::string > res;
  std::string prefix = "";
  in >> prefix;
  using namespace std::placeholders;
  auto isStartWith = std::bind(startsWith, _1, prefix);
  std::copy_if(searchDict.begin(), searchDict.end(), std::inserter(res, res.end()), isStartWith);
  if (res.empty())
  {
    out << "There aren't any words in " << dict << " with prefix " << prefix << ".\n";
    return;
  }
  mainMap[newDict] = res;
}

void namestnikov::doPostfix(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string newDict = "";
  in >> newDict;
  std::string dict = "";
  in >> dict;
  std::unordered_map< std::string, std::string > searchDict = mainMap.at(dict);
  if (searchDict.empty())
  {
    out << dict << " is empty.\n";
    return;
  }
  std::unordered_map< std::string, std::string > res;
  std::string postfix = "";
  in >> postfix;
  using namespace std::placeholders;
  auto isEndWith = std::bind(endsWith, _1, postfix);
  std::copy_if(searchDict.begin(), searchDict.end(), std::inserter(res, res.end()), isEndWith);
  if (res.empty())
  {
    out << "There aren't any words in " << dict << " with postfix " << postfix << ".\n";
    return;
  }
  mainMap[newDict] = res;
}

bool hasBetween(const std::pair< std::string, std::string > & pairDict, const std::string & sub)
{
  size_t strLength = pairDict.first.size();
  size_t subLength = sub.size();
  if (pairDict.first == sub)
  {
    return true;
  }
  if (strLength < subLength)
  {
    return false;
  }
  bool check = false;
  for (size_t i = 0; i <= strLength - subLength; ++i)
  {
    check = check || (pairDict.first.compare(i, subLength, sub) == 0);
  }
  return (check && (!startsWith(pairDict, sub)) && (!endsWith(pairDict, sub)));
}

void namestnikov::doSuffix(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string newDict = "";
  in >> newDict;
  std::string dict = "";
  in >> dict;
  std::unordered_map< std::string, std::string > searchDict = mainMap.at(dict);
  if (searchDict.empty())
  {
    out << dict << " is empty.\n";
    return;
  }
  std::unordered_map< std::string, std::string > res;
  std::string suffix = "";
  in >> suffix;
  using namespace std::placeholders;
  auto isHasBetween = std::bind(hasBetween, _1, suffix);
  std::copy_if(searchDict.begin(), searchDict.end(), std::inserter(res, res.end()), isHasBetween);
  if (res.empty())
  {
    out << "There aren't any words in " << dict << " with suffix " << suffix << ".\n";
    return;
  }
  mainMap[newDict] = res;
}

void namestnikov::doPalindrome(std::istream & in, dictMain & mainMap, std::ostream & out)
{
  std::string dictName = "";
  in >> dictName;
  std::vector< std::string > palindromes;
  std::unordered_map< std::string, std::string > searchDict = mainMap.at(dictName);
  for (const auto & pair1: searchDict)
  {
    for (const auto & pair2: searchDict)
    {
      auto it = std::find(palindromes.begin(), palindromes.end(), pair1.first);
      if (it == palindromes.end())
      {
        std::string reverseStr = pair1.first;
        std::reverse(reverseStr.begin(), reverseStr.end());
        if ((reverseStr == pair2.first) && (pair1.first != pair2.first))
        {
          palindromes.push_back(pair1.first);
          palindromes.push_back(pair1.second);
          palindromes.push_back(pair2.first);
          palindromes.push_back(pair2.second);
        }
      }
    }
  }
  if (palindromes.size() == 0)
  {
    out << "There aren't any palindromes in " << dictName << ".\n";
    return;
  }
  using output_it_t = std::ostream_iterator< std::string >;
  std::copy(palindromes.cbegin(), palindromes.cend(), output_it_t{out, " "});
  out << "\n";
}
