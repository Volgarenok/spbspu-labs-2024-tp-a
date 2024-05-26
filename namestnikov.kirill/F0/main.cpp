#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <string>

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
  myMap.insert({"first", tempMap});
  myMap.insert({"second", tempMap2});
  for (auto itr = myMap["first"].begin(); itr != myMap["first"].end(); itr++) { 
        std::cout << itr->first 
             << '\t' << itr->second << '\n'; 
  }
  doCreate(std::cin, std::cout, myMap);
  doUnique(std::cin, std::cout, myMap);
  doFind(std::cin, std::cout, myMap);
}
