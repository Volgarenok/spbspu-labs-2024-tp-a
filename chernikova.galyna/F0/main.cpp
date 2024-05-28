#include <iostream>
#include <map>
#include <string>
#include "Dictionary.hpp"
#include "interface.hpp"
#include "commands.hpp"

int main()
{
  using namespace chernikova;

  std::map< std::string, Dictionary > dataBase = {};
  std::string command = "";
  
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
