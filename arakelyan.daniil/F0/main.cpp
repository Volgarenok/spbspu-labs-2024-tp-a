#include <iostream>
#include <limits>
#include <map>
#include <stdexcept>
#include <vector>
#include <functional>

#include "cmds.hpp"

int main()
{
  using namespace arakelyan;

  using dictionaries_t = std::map< std::string, std::map< std::string,
                          std::vector< std::string > > >;

  dictionaries_t dictionaryOfDictionaries;

  using func = std::function< void(std::istream&, std::ostream&, dictionaries_t&) >;

  std::map< std::string, func > commands;

  commands["new"] = addDictionary;
  commands["delete"] = deleteDictionary;
  commands["add"] = addWord;
  commands["remove"] = removeWord;
  commands["translate"] = wordTranslations;
  commands["merge"] = mergeDictionaries;
  commands["move"] = moveWords;
  commands["list"] = showAllDictionariesNames;
  commands["size"] = getSizeOfDictionary;
  commands["print"] = printTranslations;
  commands["intersect"] = intersectDictionaries;
  commands["complement"] = complement;
  commands["popular-aggregator"] = popularAggregator;

  while (!std::cin.eof())
  {
    try
    {
      std::string cmd = "";
      std::cin >> cmd;
      if (cmd == "help")
      {
        helpCommand(std::cout);
        continue;
      }
      commands.at(cmd)(std::cin, std::cout, dictionaryOfDictionaries);
    }
    catch (const std::out_of_range &e)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
