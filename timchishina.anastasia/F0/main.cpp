#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <functional>
#include <limits>
#include "commands.hpp"

using namespace timchishina;
int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "<INVALID ARGUMENTS>\n";
    return 1;
  }
  std::string arg(argv[1]);
  if (arg == "--help")
  {
    doHelp(std::cout);
  }
  std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > > dictionaries;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  using namespace std::placeholders;
  cmds["create"] = std::bind(doCreate, std::ref(dictionaries), _1, _2);
  cmds["delete"] = std::bind(doDelete, std::ref(dictionaries), _1, _2);
  cmds["print"] = std::bind(doPrint, std::ref(dictionaries), _1, _2);
  cmds["add"] = std::bind(doAdd, std::ref(dictionaries), _1, _2);
  cmds["remove"] = std::bind(doRemove, std::ref(dictionaries), _1, _2);

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
