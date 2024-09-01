#include <cstring>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include <streamGuard.hpp>

#include "commands.hpp"
#include "dictionary.hpp"

int main(int argc, char *argv[])
{
  if (argc >= 2)
  {
    if (strcmp(argv[1], "--help") == 0)
    {
      zagrivnyy::help();
    }
    else if (strcmp(argv[1], "--check") == 0)
    {
      zagrivnyy::check(argv[2]);
    }
    else
    {
      std::cerr << "unknown option: " << argv[1] << "\n";
      std::cerr << "possible options: [--help] [--check <file>]\n";
      return 1;
    }
    return 0;
  }

  std::map< std::string, zagrivnyy::Dictionary > dictionaries;

  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["read"] = std::bind(zagrivnyy::read, std::ref(dictionaries), _1);
    cmds["list"] = std::bind(zagrivnyy::list, std::cref(dictionaries), _1, _2);
    cmds["delete"] = std::bind(zagrivnyy::deleteDict, std::ref(dictionaries), _1);
  }

  std::string cmd;
  zagrivnyy::StreamGuard streamGuard(std::cout);
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
