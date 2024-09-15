#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <limits>
#include "cmds.hpp"

int main() {
  using namespace altun;
  std::map< std::string, std::map< std::string, std::vector< std::string > > > dictionaries = {};
  using funcName = std::function< void(std::istream&, std::map< std::string, std::map< std::string, std::vector< std::string > > >&) >;
  std::map< std::string, funcName > cmds = {};
  {
    using namespace std::placeholders;
    cmds["create"] = createDictionary;
    cmds["delete"] = deleteDictionary;
  }
  while (!std::cin.eof())
  {
    try
    {
      std::string cmd_name = "";
      std::cin >> cmd_name;
      cmds.at(cmd_name)(std::cin, dictionaries);
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