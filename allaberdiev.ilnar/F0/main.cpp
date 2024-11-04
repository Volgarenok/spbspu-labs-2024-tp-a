#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <limits>
#include "commands.hpp"

int main() {
  using namespace allaberdiev;
  std::map< std::string, std::map< std::string, std::vector< std::string > > > dicts = {};
  using funcName = std::function< void(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&) >;
  std::map< std::string, funcName > commands = {};
  {
    using namespace std::placeholders;
    commands["create"] = createDict;
    commands["delete"] = deleteDict;
    commands["add"] = addWord;
    commands["remove"] = removeWord;
    commands["translate"] = std::bind(translateWord, std::ref(std::cout), _1, _2);
    commands["merge"] = mergeDict;
    commands["combining"] = combineDict;
  }

  while (!std::cin.eof())
  {
    try
    {
      std::string commandName = "";
      std::cin >> commandName;
      commands.at(commandName)(std::cin, dicts);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
