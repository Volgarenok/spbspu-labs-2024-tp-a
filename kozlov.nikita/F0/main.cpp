#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <functional>
#include "commands.hpp"

using namespace kozlov;
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
    doCmdHelp(std::cout);
  }
  std::map< std::string, std::map< std::string, size_t > > dictionaries = {};

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  using namespace std::placeholders;
  cmds["create"] = std::bind(doCmdCreate, std::ref(dictionaries), _1, _2);
  cmds["print"] = std::bind(doCmdPrint, std::ref(dictionaries), _1, _2);
  cmds["delete"] = std::bind(doCmdDelete, std::ref(dictionaries), _1, _2);
  cmds["add"] = std::bind(doCmdAdd, std::ref(dictionaries), _1, _2);
  cmds["remove"] = std::bind(doCmdRemove, std::ref(dictionaries), _1, _2);
  cmds["count"] = std::bind(doCmdCount, std::ref(dictionaries), _1, _2);
  cmds["save"] = std::bind(doCmdSave, std::ref(dictionaries), _1, _2);
  cmds["load"] = std::bind(doCmdLoad, std::ref(dictionaries), _1, _2);
  cmds["merge"] = std::bind(doCmdMerge, std::ref(dictionaries), _1, _2);

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
