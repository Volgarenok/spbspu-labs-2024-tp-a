#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <limits>
#include <map>

#include "Hash.hpp"
#include "Commands.hpp"

int main()
{
  std::map< std::string, zaparin::HashTable > dicts;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
