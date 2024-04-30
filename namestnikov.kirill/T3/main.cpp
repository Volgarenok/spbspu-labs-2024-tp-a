#include <iostream>
#include <fstream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <map>
#include <limits>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  if (argc != 2)
  {
    std::cerr << "Wrong command line arguments\n";
    return 1;
  }
  else
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Can not open file\n";
      return 1;
    }
    using input_it_t = std::istream_iterator< namestnikov::Polygon >;
    std::vector< namestnikov::Polygon > data;
    std::copy(input_it_t{in}, input_it_t{}, std::back_inserter(data));
    std::map< std::string, std::function< void(std::vector< namestnikov::Polygon > &, std::istream &, std::ostream &) > > commands;
    {
      commands["AREA"] = getArea;
      commands["COUNT"] = getCount;
      commands["MAX"] = getMax;
      commands["MIN"] = getMin;
    }
    std::string commandName = "";
    while (std::cin >> commandName)
    {
      try
      {
        commands.at(commandName)(data, std::cin, std::cout);
        std::cout << "\n";
      }
      catch (...)
      {
        std::cerr << "<INVALID COMMAND>\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
