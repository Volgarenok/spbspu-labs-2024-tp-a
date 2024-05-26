#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include "commands.hpp"

using namespace std::placeholders;

void addDictionary(std::string& dictionaryName, dictionaryOne& toAdd, dict& dictionary)
{
  if (toAdd.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  if (dictionary.find(dictionaryName) != dictionary.cend())
  {
    dictionary[dictionaryName] = std::move(toAdd);
  }
  else
  {
    dictionary[dictionaryName] = toAdd;
  }
}

void zakozhurnikova::print(const std::list< std::string >& args, const dict& dictionary)
{
  if (args.size() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }
  std::string result;
  std::string mapName = args.back();
  if (!dictionary.at(mapName).empty())
  {
    result = mapName + ' ';
    for (auto it = dictionary.at(mapName).cbegin(); it != dictionary.at(mapName).cend(); ++it)
    {
      result += it->first + ' ';
      for (auto itList = (it->second).begin(); itList != (it->second).end(); ++itList)
      {
        result += *itList + ' ';
      }
    }
    result.pop_back();
  }
  else
  {
    result = "<EMPTY>";
  }
  std::cout << result << '\n';
}

bool identical(const dictionaryOne& second, std::pair< std::string, std::set< std::string > > word)
{
  return second.find(word.first) == second.cend();
}

void zakozhurnikova::complement(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;
  auto predicate = std::bind(identical, std::cref(secondMap), _1);
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

void zakozhurnikova::intersect(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;
  auto predicate = std::bind(std::logical_not< bool >{}, std::bind(identical, std::cref(secondMap), _1));
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

void zakozhurnikova::doUnion(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }

  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;

  copy(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()));
  auto predicate = std::bind(identical, std::cref(resultDict), _1);
  std::copy_if(secondMap.cbegin(), secondMap.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

bool checkSymbol(const std::string& temp)
{
  if (temp.size() != 1 || !((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z')))
  {
    return false;
  }
  return true;
}

bool isSymbol(const std::string& symbol, std::pair< std::string, std::set< std::string > > pair)
{
  std::string temp = pair.first;
  return temp[0] == symbol[0];
}

void zakozhurnikova::specificLetter(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("Incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.back());
  args.pop_back();
  std::string symbol = args.back();
  if (!checkSymbol(symbol))
  {
    throw std::invalid_argument("Incorrect symbol");
  }
  dictionaryOne resultDict;
  auto predicate = std::bind(isSymbol, symbol, _1);
  copy_if(current.cbegin(), current.cend(), std::inserter(resultDict, resultDict.end()), predicate);
  addDictionary(args.front(), resultDict, dictionary);
}

void zakozhurnikova::elimination(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 3)
  {
    throw std::invalid_argument("incorrect command source");
  }
  dictionaryOne& current = dictionary.at(args.front());
  args.pop_front();
  std::string word = args.front();
  args.pop_front();
  std::string translate = args.front();
  std::set< std::string >& temp = current[word];
  if (!temp.empty())
  {
    temp.clear();
  }
  temp.insert(translate);
  current[word] = temp;
}

void zakozhurnikova::destruction(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  try
  {
    dictionaryOne& current = dictionary.at(args.front());
    std::string word = args.back();
    current.erase(word);
  }
  catch (const std::out_of_range& e)
  {
    std::cout << "The word was not found\n";
  }
}

void zakozhurnikova::addition(std::list< std::string >& args, dict& dictionary)
{
  if (args.size() != 2)
  {
    throw std::invalid_argument("incorrect command source");
  }
  dictionaryOne& secondMap = dictionary.at(args.back());
  args.pop_back();
  dictionaryOne& firstMap = dictionary.at(args.back());
  dictionaryOne resultDict;
  auto predicateFirst = std::bind(identical, std::cref(secondMap), _1);
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDict, resultDict.end()), predicateFirst);
  auto predicateSecond = std::bind(std::logical_not< bool >{}, std::bind(identical, std::cref(firstMap), _1));
  std::copy_if(secondMap.cbegin(), secondMap.cend(), std::inserter(resultDict, resultDict.end()), predicateSecond);

  firstMap.clear();
  firstMap = resultDict;
}
