#include <iostream>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <limits>
#include <string>
#include <algorithm>
#include "delimeters.hpp"
#include "commands.hpp"

int main()
{
  using pairWords = std::pair< std::string, std::string >;
  using dictMain = std::unordered_map< std::string, std::unordered_map< std::string, std::string > >;
  using namespace namestnikov;
  std::ifstream in("base.txt");
  std::unordered_map< std::string, std::unordered_map< std::string, std::string > > myMap;
  std::unordered_map< std::string, std::string > tempMap;
  std::unordered_map< std::string, std::string > tempMap2;
  tempMap.insert({"cat", "кошка"});
  tempMap.insert({"dog", "собака"});
  tempMap2.insert({"me", "мне"});
  tempMap2.insert({"I", "я"});
  tempMap2.insert({"dog", "собака"});
  tempMap2.insert({"god", "бог"});
  tempMap2.insert({"melon", "дыня"});
  tempMap2.insert({"baloon", "шар"});

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
  //doPalindrome(std::cin, std::cout, myMap);
  std::unordered_map< std::string, std::function< void(std::istream &, dictMain &, std::ostream &) > > commands;
  {
    using namespace std::placeholders;
    commands["add"] = doAdd;
    commands["find"] = doFind;
    commands["postfix"] = doPostfix;
    commands["remove"] = doRemove;
    commands["unique"] = doUnique;
    commands["merge"] = doMerge;
    commands["export"] = doExport;
    commands["palindrome"] = doPalindrome;
    commands["import"] = doImport;
    commands["prefix"] = doPrefix;
    commands["create"] = doCreate;
    commands["suffix"] = doSuffix;
  }
  commands.at("palindrome")(std::cin, myMap, std::cout);
  //doImport(std::cin, std::cout, myMap);
  //std::cout << myMap["first"]["dog"];
  //std::cout << myMap["first"].size();
  //doSuffix(std::cin, std::cout, myMap);
  //std::cout << myMap["res"]["melon"];
}
