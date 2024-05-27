#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <limits>
#include "commands.hpp"

int main()
{
  using namespace baranov;
  std::map< std::string, std::map< std::string, size_t > > dictionaries;
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > commands;
  {
    using namespace std::placeholders;
    commands["create"] = std::bind(create, std::ref(dictionaries), _1, _2);
  }

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

