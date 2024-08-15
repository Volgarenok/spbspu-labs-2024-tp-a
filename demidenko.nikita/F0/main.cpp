#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include "commands.hpp"
#include "dictionary.hpp"

int main(int argc, char** argv)
{
  if (argc > 3)
  {
    return 1;
  }
  if (argc > 1)
  {
    if (std::strcmp(argv[1], "--help") == 0)
    {
      demidenko::doHelpCmd(std::cout);
      return 0;
    }
    if (std::strcmp(argv[1], "--check") == 0)
    {
      if (argc < 3)
      {
        return 1;
      }
      demidenko::doCheckCmd(std::cout, argv[2]);
      return 0;
    }
  }
  std::map< std::string, demidenko::Dictionary > dictionaries;
  if (argc > 1)
  {
    std::ifstream in;
    if (argc == 2)
    {
      in.open(argv[1]);
    }
    else
    {
      in.open(argv[2]);
    }
    in >> dictionaries[argv[1]];
    if (in.fail())
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }
  std::string cmd;
  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  commands["add"] = std::bind(demidenko::doAddCmd, _1, std::ref(dictionaries));
  commands["remove"] = std::bind(demidenko::doRemoveCmd, _1, std::ref(dictionaries));
  commands["save"] = std::bind(demidenko::doSaveCmd, _1, std::ref(dictionaries));
  commands["load"] = std::bind(demidenko::doLoadCmd, _1, std::ref(dictionaries));
  commands["list"] = std::bind(demidenko::doListCmd, _2, std::ref(dictionaries));
  commands["translate"] = std::bind(demidenko::doTranslateCmd, _1, _2, std::ref(dictionaries));
  commands["search"] = std::bind(demidenko::doSearchCmd, _1, _2, std::ref(dictionaries));
  commands["prefix"] = std::bind(demidenko::doPrefixCmd, _1, _2, std::ref(dictionaries));
  commands["merge"] = std::bind(demidenko::doMergeCmd, _1, std::ref(dictionaries));
  commands["exclude"] = std::bind(demidenko::doExcludeCmd, _1, std::ref(dictionaries));
  commands["split"] = std::bind(demidenko::doSplitCmd, _1, std::ref(dictionaries));
  std::cin >> cmd;
  while (!std::cin.eof())
  {
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin >> cmd;
  }
}
