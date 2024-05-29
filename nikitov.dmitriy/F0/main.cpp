#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <functional>
#include "dictionary.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;

  std::map< std::string, Dictionary > dictOfDicts;
  if (argc != 1)
  {
    if (std::string(argv[1]) == "--dicts")
    {
      for (int i = 2; i != argc; ++i)
      {
        std::ifstream fileInput(argv[i]);
        if (fileInput)
        {
          Dictionary dict;
          fileInput >> dict;
          dictOfDicts.insert({ argv[i], dict });
        }
      }
    }
    else if (std::string(argv[1]) == "--help")
    {
      printHelp(std::cout);
      return 0;
    }
  }

  using namespace std::placeholders;
  std::map< std::pair< std::string, std::string >, std::function< void(const std::map< std::string, Dictionary >&, std::istream&,
    std::ostream&) > > constCommands;
  constCommands[{ "print", "dictionary" }] = printDictCmd;
  constCommands[{ "print", "all" }] = printAllCmd;
  constCommands[{ "print", "names" }] = printNamesCmd;
  constCommands[{ "find", "translation" }] = std::bind(findCmd, _1, _2, _3, "translation");
  constCommands[{ "find", "antonym" }] = std::bind(findCmd, _1, _2, _3, "antonym");
  constCommands[{ "translate", "sentence" }] = translateSentenceCmd;
  constCommands[{ "translate", "file" }] = translateFileCmd;
  constCommands[{ "save", "dictionary" }] = saveCmd;

  std::map< std::pair< std::string, std::string >, std::function< void(std::map< std::string, Dictionary >&, std::istream&) > > commands;
  commands[{ "create", "dictionary" }] = createCmd;
  commands[{ "add", "translation" }] = std::bind(addCmd, _1, _2, "translation");
  commands[{ "add", "antonym" }] = std::bind(addCmd, _1, _2, "antonym");
  commands[{ "edit", "primary" }] = std::bind(editCmd, _1, _2, "primary");
  commands[{ "edit", "secondary" }] = std::bind(editCmd, _1, _2, "secondary");
  commands[{ "delete", "primary" }] = std::bind(deleteCmd, _1, _2, "primary");
  commands[{ "delete", "secondary" }] = std::bind(deleteCmd, _1, _2, "secondary");
  commands[{ "delete", "antonym" }] = std::bind(deleteCmd, _1, _2, "antonym");
  commands[{ "merge", "dictionary"}] = mergeCmd;


  std::string command;
  std::string parameter;
  while (std::cin >> command && std::cin >> parameter)
  {
    try
    {
      constCommands.at({ command, parameter })(dictOfDicts, std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        commands.at({ command, parameter })(dictOfDicts, std::cin);
      }
      catch (const std::out_of_range&)
      {
        std::cerr << "<ERROR: INVALID COMMAND>" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
