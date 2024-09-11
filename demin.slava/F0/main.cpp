#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "commands.hpp"

int main(int argc, char *argv[])
{
  if (argc > 1 && std::string(argv[1]) == "--help")
  {
    demin::showHelp();
    return 0;
  }

  if (argc > 2 && std::string(argv[1]) == "--check")
  {
    std::ifstream file(argv[2]);
    if (file)
    {
      std::cout << "File is valid" << std::endl;
    }
    else
    {
      std::cout << "INVALID COMMAND" << std::endl;
    }
    return 0;
  }

  std::map< std::string, std::vector< std::string > > crossReferences;

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["read"] = std::bind(demin::read, std::ref(crossReferences), _1);
    cmds["out"] = std::bind(demin::out, std::ref(crossReferences), _1, _2);
    cmds["add"] = std::bind(demin::add, std::ref(crossReferences), _1);
    cmds["remove"] = std::bind(demin::remove, std::ref(crossReferences), _1);
    cmds["delete"] = std::bind(demin::deleteList, std::ref(crossReferences), _1);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}

