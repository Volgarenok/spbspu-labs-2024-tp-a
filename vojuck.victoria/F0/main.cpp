#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "command.hpp"

int main(int argc, char * argv[])
{
  using namespace vojuck;
  std::map< std::string, std::map< std::string, size_t > > dictionaries;
  std::map< std::string, std::function< void(char **, std::ostream &) > > arguments;
  {
    using namespace std::placeholders;
    arguments["--help"] = std::bind(printHelp, _2);
  }
  if (argc >= 2)
  {
    std::string argument = argv[1];
    try
    {
      arguments.at(argument)(argv, std::cout);
      return 0;
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>";
    }
  }
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > commands;
  {
    using namespace std::placeholders;
    commands["make"] = std::bind(makeCmd, std::ref(dictionaries), _1, _2);
    commands["delete"] = std::bind(deleteCmd, std::ref(dictionaries), _1, _2);
    commands["load"] = std::bind(loadCmd, std::ref(dictionaries), _1, _2);
    commands["add"] = std::bind(addCmd, std::ref(dictionaries), _1, _2);
   // commands["save"] = std::bind(saveDictToFile, std::ref(dictionaries), _1, _2);
    commands["remove"] = std::bind(removeCmd, std::ref(dictionaries), _1, _2);
    commands["print"] = std::bind(wordFrequency, std::ref(dictionaries), _1, _2);
    commands["merge"] = std::bind(mergeDict, std::ref(dictionaries), _1, _2);
    commands["merge_unique"] = std::bind(uniqueFreq, std::ref(dictionaries), _1, _2);
    commands["intersection"] = std::bind(intersection, std::ref(dictionaries), _1, _2);
    commands["min_freaq"] = std::bind(minFreq, std::ref(dictionaries), _1, _2);
    commands["max_freaq"] = std::bind(maxFreq, std::ref(dictionaries), _1, _2);
    commands["more_freaq"] = std::bind(moreFreq, std::ref(dictionaries), _1, _2);
    commands["less_freaq"] = std::bind(lessFreq, std::ref(dictionaries), _1, _2);
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
  }
  std::cin.clear();
  std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}
