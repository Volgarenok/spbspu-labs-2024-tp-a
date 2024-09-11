#include <iostream>
#include <map>
#include <string>
#include "commands.hpp"
#include "arguements.hpp"
#include "dictionary.hpp"

int main(int argc, char* argv[])
{
  using namespace chernikova;

  std::map< std::string, Dictionary > dataBase = {};

  if (!processArguements(argv, argc, dataBase))
  {
    return 0;
  }

  while (!std::cin.eof())
  {
    if (!doCommand(dataBase))
    {
      break;
    }
  }

  return 0;
}
