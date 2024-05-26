#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
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
    dictionary[dictionaryName] =  toAdd;
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
  dictionaryOne resultDictionary;
  auto predicate = std::bind(identical, std::cref(secondMap), _1);
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDictionary, resultDictionary.end()), predicate);
  addDictionary(args.front(), resultDictionary, dictionary);
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
  dictionaryOne resultDictionary;
  auto predicate = std::bind(std::logical_not< bool >{}, std::bind(identical, std::cref(secondMap), _1));
  std::copy_if(firstMap.cbegin(), firstMap.cend(), std::inserter(resultDictionary, resultDictionary.end()), predicate);
  addDictionary(args.front(), resultDictionary, dictionary);
}
