#include <iostream>
#include <fstream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include "figures_struct.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;

  std::vector< Polygon > data;
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    using input_it_t = std::istream_iterator< Polygon >;
    while (!input.eof())
    {
      if (input.fail())
      {
        input.clear();
        input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
      std::copy(input_it_t{ input }, input_it_t{}, std::back_inserter(data));
    }
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  std::map< std::string, std::function< void(const std::vector< Polygon >&, std::istream&, std::ostream&) > > commands;
  commands["AREA"] = areaCmd;
  commands["COUNT"] = countCmd;
  commands["MAX"] = maxCmd;
  commands["MIN"] = minCmd;
  commands["SAME"] = sameCmd;
  commands["PERMS"] = permsCmd;

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(data, std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
