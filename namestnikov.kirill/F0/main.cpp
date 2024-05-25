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
}
