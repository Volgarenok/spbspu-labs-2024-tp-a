#include <iostream>
#include <map>
#include <vector>
#include <functional>

#include "cmds.hpp"

int main()
{
  using namespace arakelyan;

  // мапа словарей
  std::map< std::string, std::map< std::string, std::vector< std::string > > > dictionaryOfDictionaries;

  using func = std::function< void(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&) >;

  std::map< std::string, func > commands;
  {
    using namespace std::placeholders;
    commands["new"] = addDictionary;
    commands["delete"] = deleteDictionary;
    commands["add"] = addWord;
    commands["remove"] = removeWord;
    commands["translate"] = std::bind(wordTranslations, std::ref(std::cout), _1, _2);
    commands["merge"] = mergeDictionaries;
    commands["move"] = moveWords;
    commands["list"] = std::bind(showAllDictionaries, std::ref(std::cout), _1, _2);
    // commands["list"] = showAllDictionaries;
    // commands["size"] = getSizeOfDictionary;
  }
}
