#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include "table.hpp"

namespace babinov
{}

int main()
{
  std::unordered_map< std::string, babinov::Table > tables;
  std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
  }
  std::string cmd;
  std::cout << "==$ ";

  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    std::cout << "==$ ";
  }
  return 0;
}
