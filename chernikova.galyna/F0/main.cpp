#include <iostream>
#include <map>
#include <string>
#include <delimiter.hpp>
#include <interface.hpp>
#include "dictionary.hpp"
#include "commands.hpp"
#include "arguements.hpp"

int main(int argc, char* argv[])
{
  using namespace chernikova;

  std::map< std::string, Dictionary > dataBase = {};

  if (!processArguements(argv, argc, dataBase))
    return 0;

  std::string command;

  while (!std::cin.eof())
  {
    std::cin >> command;

    if (std::cin.eof())
    {
      break;
    }

    if (!std::cin)
    {
      handleError();
      continue;
    }

    std::cin >> PunctuationI{ ' ' };

    if (!std::cin)
    {
      handleError();
      continue;
    }

    doCommand(dataBase, command);
  }
  return 0;
}
