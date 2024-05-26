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

  using namespace std::placeholders;

  std::map< std::string, std::function< void(std::istream&, std::ostream&, allDicts) > > commands;
  commands["addWord"] = std::bind(addWord, _1, dicts);
  commands["addTranslation"] = std::bind(addTranslation, _1, dicts);
  commands["searchWord"] = std::bind(searchWord, _1, _2, dicts);
  commands["searchTranslation"] = std::bind(searchTranslation, _1, _2, dicts);
  commands["deleteWord"] = std::bind(deleteWord, _1, dicts);
  commands["deleteTranslation"] = std::bind(deleteTranslation, _1, dicts);
  commands["findSynonyms"] = std::bind(findSynonyms, _1, _2, dicts);
  commands["countWords"] = std::bind(countWords, _1, _2, dicts);
  commands["intersect"] = std::bind(intersect, _1, dicts);
  commands["subtract"] = std::bind(subtract, _1, dicts);
  commands["merge"] = std::bind(merge, _1, dicts);


  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, dicts);
      std::cout << '\n';
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
