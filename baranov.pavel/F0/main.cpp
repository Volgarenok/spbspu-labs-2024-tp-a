#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "commands.hpp"
#include "CLA.hpp"

int main(int argc, char * argv[])
{
  using namespace baranov;
  std::map< std::string, std::map< std::string, size_t > > dictionaries;
  std::map< std::string, std::function< void(char **, std::ostream &) > > arguments;
  {
    using namespace std::placeholders;
    arguments["--help"] = std::bind(printHelp, _2);
    arguments["--check"] = checkDictFile;
    arguments["--create"] = createDict;
  }
  if (argc >= 2)
  {
    std::string argument = argv[1];
    try
    {
      arguments.at(argument)(argv, std::cout);
      return 0;
    }
    catch (const std::out_of_range &)
    {
      loadDict(argv[1], dictionaries);
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID CLA>\n";
    }

  }
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > commands;
  {
    using namespace std::placeholders;
    commands["create"] = std::bind(createCmd, std::ref(dictionaries), _1, _2);
    commands["clear"] = std::bind(clearCmd, std::ref(dictionaries), _1, _2);
    commands["delete"] = std::bind(deleteCmd, std::ref(dictionaries), _1, _2);
    commands["addwords"] = std::bind(addWordsCmd, std::ref(dictionaries), _1, _2);
    commands["printcount"] = std::bind(printCountCmd, std::cref(dictionaries), _1, _2);
    commands["printdict"] = std::bind(printDictCmd, std::cref(dictionaries), _1, _2);
    commands["printtop"] = std::bind(printTopCmd, std::cref(dictionaries), _1, _2);
    commands["join"] = std::bind(joinCmd, std::ref(dictionaries), _1, _2);
    commands["intersect"] = std::bind(intersectCmd, std::ref(dictionaries), _1, _2);
    commands["save"] = std::bind(saveCmd, std::cref(dictionaries), _1, _2);
    commands["lsdicts"] = std::bind(lsDictsCmd, std::cref(dictionaries), _1, _2);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

