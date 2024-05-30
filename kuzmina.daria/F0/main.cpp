#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <limits>
#include <functional>
#include "Commands.hpp"

using namespace kuzmina;

int main(int argc, char* argv[])
{
  if (argc == 2 and std::string(argv[1]) == "--help")
  {
    showHelp(std::cout);
  }
  else if (argc != 1)
  {
    std::cerr << "Wrong input parameters";
    return 1;
  }

  allDicts dicts;
  Dict dict1, dict2, dict3;
  dicts["dict1"] = dict1;
  dicts["dict2"] = dict2;
  dicts["dict3"] = dict3;

  using namespace std::placeholders;

  std::map< std::string, std::function< void(std::istream&, std::ostream&, allDicts&) > > commands;
  commands["addWord"] = std::bind(addWord, _1, _3);
  commands["addTranslation"] = std::bind(addTranslation, _1, _3);
  commands["searchWord"] = std::bind(searchWord, _1, _2, _3);
  commands["searchTranslation"] = std::bind(searchTranslation, _1, _2, _3);
  commands["deleteWord"] = std::bind(deleteWord, _1, _3);
  commands["deleteTranslation"] = std::bind(deleteTranslation, _1, _3);
  commands["findSynonyms"] = std::bind(findSynonyms, _1, _2, _3);
  commands["countWords"] = std::bind(countWords, _1, _2, _3);
  commands["intersect"] = std::bind(intersect, _1, _3);
  commands["subtract"] = std::bind(subtract, _1, _3);
  commands["merge"] = std::bind(merge, _1, _3);
  commands["print"] = std::bind(print, _1, _2, _3);

  std::string command, dictName;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, dicts);
      std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cout << "Invalid command or dictionary name\n";

      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
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
