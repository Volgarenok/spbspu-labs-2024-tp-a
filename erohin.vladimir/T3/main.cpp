#include <iostream>
#include <map>
#include <functional>
#include <limits>
#include <fstream>
#include "polygon.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 2)
  {
    std::cerr << "Wrong CLA number\n";
    return 1;
  }
  std::fstream file(argv[1]);
  Polygon pol;
  file >> pol;
  std::cout << pol.points.back().x << " " << pol.points.back().y;
  file.close();
  using func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, func > command;
  std::string command_name;
  std::cin >> command_name;
  while (!std::cin.eof())
  {
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (const std::exception & e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> command_name;
  }
  return 0;
}
