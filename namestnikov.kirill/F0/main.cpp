#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <limits>
#include <string>
#include "delimeters.hpp"

void doHelp(std::ostream & out)
{
  out << "Available commands:\n";
  out << "add <dict> <key> <translation> - add new word with translation to the dictionary\n";
  out << "find <dict> <key> - find a word by the key in dictionary\n";
  out << "remove <dict> <key> - remove a word by the key in the dictionary\n";
  out << "unique <resdict> <dict1> <dict2> - make a dictionary with unique words from two dictionaries\n";
  out << "merge <resdict> <dict1> <dict2> - make a dictionary with all words from two dictionaries\n";
  out << "export <dict> <filename> - export a dictionary to file\n";
  out << "palindrome <dict> - find all words-palindroms in dictionary\n";
  out << "import <dict> <filename> - import a dictionary from file\n";
  out << "prefix <newdict> <dict> <prefix> - make a new dictionary with words that has this prefix\n";
  out << "postfix <newdict> <dict> <postfix> - make a new dictionary with words that has this postfix\n";
  out << "suffix <newdict> <dict> <suffix> - make a new dictionary with words that has this suffix\n";
}

void doCreate(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
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

void doAdd(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
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

void doFind(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
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

void doRemove(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
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

void doUnique(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
{
  std::string resDict = "";
  in >> resDict;
  std::string firstDict = "";
  in >> firstDict;
  std::string secondDict = "";
  in >> secondDict;
  std::unordered_map< std::string, std::string > res;
  std::unordered_map< std::string, std::string > first = mainMap[firstDict];
  std::unordered_map< std::string, std::string > second = mainMap[secondDict];
  for (const auto & key1: first)
  {
    if (res.find(key1.first) == res.end())
    {
      res.insert(key1);
    }
  }
  for (const auto & key2: second)
  {
    if (res.find(key2.first) == res.end())
    {
      res.insert(key2);
    }
  }
  mainMap[resDict] = res;
  out << "Dictionary " << resDict << " is successfully created.\n";
}

void doExport(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
{
  std::string dict = "";
  in >> dict;
  std::string filename = "";
  in >> filename;
  std::ofstream outFile(filename);
  if (!outFile.is_open())
  {
    throw std::invalid_argument("Can't open this file");
  }
  outFile << dict << "\n";
  for (const auto & pair: mainMap[dict])
  {
    outFile << pair.first << "-" << pair.second << "\n";
  }
}

void doImport(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
{
  std::string dict = "";
  in >> dict;
  std::string filename = "";
  in >> filename;
  std::ifstream inFile(filename);
  if (!inFile.is_open())
  {
    throw std::invalid_argument("Can't open this file");
  }
  using delS = namestnikov::DelimeterString;
  std::string dictName = "";
  std::getline(inFile, dictName, '\n');
  std::unordered_map< std::string, std::string > res;
  while (!inFile.eof())
  {
    inFile.clear();
    std::string key = "";
    std::string value = "";
    inFile >> key >> delS{"-"} >> value >> delS{"\n"};
    std::cout << key << "||||" << value;
    res.insert(std::make_pair(key, value));
    //inFile.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  mainMap[dictName] = res;
}

bool startsWith(const std::string & str, const std::string & sub)
{
  size_t strLength = str.size();
  size_t subLength = sub.size();
  return ((strLength >= subLength) && (str.compare(0, subLength, sub) == 0));
}

void doPrefix(std::istream & in, std::ostream & out, std::unordered_map< std::string, std::unordered_map< std::string, std::string > > & mainMap)
{
  std::string newDict = "";
  in >> newDict;
  std::string dict = "";
  in >> dict;
  std::unordered_map< std::string, std::string > searchDict = mainMap[dict];
  std::unordered_map< std::string, std::string > res;
  std::string prefix = "";
  in >> prefix;
  for (const auto & pair: searchDict)
  {
    if (startsWith(pair.first, prefix))
    {
      res.insert(pair);
    }
  }
  mainMap[newDict] = res;
}

bool endsWith(const std::string & str, const std::string & sub)
{
  size_t strLength = str.size();
  size_t subLength = sub.size();
  return ((strLength >= subLength) && (str.compare(strLength - subLength, subLength, sub) == 0));
}

int main()
{
  using pairWords = std::pair< std::string, std::string >;
  using dictMain = std::unordered_map< std::string, std::unordered_map< std::string, std::string > >;

  std::ifstream in("base.txt");
  std::unordered_map< std::string, std::unordered_map< std::string, std::string > > myMap;
  std::unordered_map< std::string, std::string > tempMap;
  std::unordered_map< std::string, std::string > tempMap2;
  tempMap.insert({"cat", "кошка"});
  tempMap.insert({"dog", "собака"});
  tempMap2.insert({"me", "мне"});
  tempMap2.insert({"I", "я"});
  tempMap2.insert({"melon", "дыня"});
  //myMap.insert({"first", tempMap});
  myMap.insert({"second", tempMap2});
  /*for (auto itr = myMap["first"].begin(); itr != myMap["first"].end(); itr++) { 
        std::cout << itr->first 
             << '\t' << itr->second << '\n'; 
  }*/
  std::cout << myMap.size();
  //doImport(std::cin, std::cout, myMap);
  /*doCreate(std::cin, std::cout, myMap);
  doUnique(std::cin, std::cout, myMap);
  doFind(std::cin, std::cout, myMap);*/
  //std::cout << myMap["first"].size();
  for (auto itr = myMap["second"].begin(); itr != myMap["second"].end(); itr++) { 
        std::cout << itr->first 
             << '\t' << itr->second << '\n'; 
  }
  doHelp(std::cout);
  doPrefix(std::cin, std::cout, myMap);
  std::cout << myMap["res"]["melon"];
}
