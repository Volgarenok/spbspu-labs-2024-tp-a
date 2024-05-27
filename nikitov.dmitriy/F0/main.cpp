#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include "dictionary.hpp"
#include "commands.hpp"
#include <functional>

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "Russian");
  using namespace nikitov;
  std::map< std::string, Dictionary > dictOfDicts;
  for (int i = 1; i != argc + 1; ++i)
  {
    std::ifstream fileInput(argv[i]);
    if (fileInput)
    {
      Dictionary dict;
      fileInput >> dict;
      dictOfDicts.insert({ argv[i], dict });
    }
  }

  std::map< std::string, std::function< void(const std::map< std::string, Dictionary >&, std::istream&, std::ostream&) > > constCommands;
  constCommands["print"] = printCmd;
  constCommands["find"] = findCmd;
  constCommands["translate"] = translateCmd;

  std::map< std::string, std::function< void(std::map< std::string, Dictionary >&, std::istream&) > > commands;
  commands["add"] = addCmd;
  commands["delete"] = deleteCmd;
  commands["edit"] = editCmd;
  commands["create"] = createCmd;

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      constCommands.at(cmd)(dictOfDicts, std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        commands.at(cmd)(dictOfDicts, std::cin);
      }
      catch (const std::out_of_range&)
      {
        std::cerr << "<INVALID COMMAND>" << '\n';
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
}
