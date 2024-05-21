#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <limits>
#include <exception>
#include "commands.hpp"

int main()
{
  using namespace kravchenko;
  std::map< std::string, FrequencyDict > dicts;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch(const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch(const std::invalid_argument& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
}
