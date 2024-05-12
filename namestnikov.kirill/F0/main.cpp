#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <string>

int main()
{
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
}
