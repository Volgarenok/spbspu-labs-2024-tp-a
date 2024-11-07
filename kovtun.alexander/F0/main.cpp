#include <iostream>
#include <map>
#include <string>
#include <functional>

#include "commands.hpp"

int main()
{
  using fun_t = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, fun_t > commands;
  kovtun::cross_t maps = kovtun::cross_t();

  commands["create"] = std::bind(kovtun::create, std::ref(maps), std::placeholders::_1, std::placeholders::_2);
  commands["remove"] = std::bind(kovtun::remove, std::ref(maps), std::placeholders::_1, std::placeholders::_2);
  commands["recover"] = std::bind(kovtun::recover, std::ref(maps), std::placeholders::_1, std::placeholders::_2);
  commands["search"] = std::bind(kovtun::search, std::ref(maps), std::placeholders::_1, std::placeholders::_2);
  commands["replace"] = std::bind(kovtun::replace, std::ref(maps), std::placeholders::_1, std::placeholders::_2);
  commands["count"] = std::bind(kovtun::count, std::ref(maps), std::placeholders::_1, std::placeholders::_2);
  commands["flush"] = std::bind(kovtun::flush, std::ref(maps), std::placeholders::_1, std::placeholders::_2);

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout);
    }
    catch (std::exception & e)
    {
      std::cerr << e.what() << "\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
