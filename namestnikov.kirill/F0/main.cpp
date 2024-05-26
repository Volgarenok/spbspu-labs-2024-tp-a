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

int main()
{
  using pairWords = std::pair< std::string, std::string >;
  using dictMain = std::unordered_map< std::string, std::unordered_map< std::string, std::string > >;

  std::ifstream in("base.txt");
  std::unordered_map< std::string, std::unordered_map< std::string, std::string > > myMap;
  std::unordered_map< std::string, std::string > tempMap;
  tempMap.insert({"cat", "кошка"});
  tempMap.insert({"dog", "собака"});
  myMap.insert({"first", tempMap});
  for (auto itr = myMap["first"].begin(); itr != myMap["first"].end(); itr++) { 
        std::cout << itr->first 
             << '\t' << itr->second << '\n'; 
  }
  doCreate(std::cin, std::cout, myMap);
  doAdd(std::cin, std::cout, myMap);
  doFind(std::cin, std::cout, myMap);
}
