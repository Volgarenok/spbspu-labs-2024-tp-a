#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "Commands.hpp"

using namespace kuzmina;

int main()
{
  allDicts dicts;
  Dict dict1, dict2;
  dicts["dict1"] = dict1;
  dicts["dict2"] = dict2;

  using namespace std::placeholders;

  std::map< std::string, std::function< void(std::istream&, std::ostream&, Dict&) > > commands;
  commands["addWord"] = std::bind(addWord, _1, _3);
  commands["addTranslation"] = std::bind(addTranslation, _1, _3);
  commands["searchWord"] = std::bind(searchWord, _1, _2, _3);
  commands["searchTranslation"] = std::bind(searchTranslation, _1, _2, _3);
  //commands["deleteWord"] = std::bind(deleteWord, _1, _3);
  //commands["deleteTranslation"] = std::bind(deleteTranslation, _1, _3);
  //commands["findSynonyms"] = std::bind(findSynonyms, _1, _2, _3);
  //commands["countWords"] = std::bind(countWords, _1, _2, _3);

  //commands["intersect"] = std::bind(intersect, _1, _3);
  //commands["subtract"] = std::bind(subtract, _1, _3);
  //commands["merge"] = std::bind(merge, _1, _3);



  std::string command, dictName;
  while (std::cin >> command)
  {
    try
    {
      std::cin >> dictName;
      commands.at(command)(std::cin, std::cout, dicts.at(dictName));
      std::cout << '\n';
    }
    //catch (const std::out_of_range& e)
    //{
    //  std::cout << "Invalid arguments: no such dictionary or wrong command\n";
    //}
    catch (const std::exception& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
