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

  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(std::cin, std::cout);
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
