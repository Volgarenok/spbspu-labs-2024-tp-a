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
    using input_it_t = std::istream_iterator< Polygon >;
    std::vector< Polygon > data;
    while (!in.eof())
    {
      std::copy(input_it_t{in}, input_it_t{}, std::back_inserter(data));
      if (in.fail())
      {
        in.clear();
        in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    std::map< std::string, std::function< void(std::istream &, std::ostream &) > > commands;
    {
      using namespace std::placeholders;
      commands["AREA"] = std::bind(getArea, std::cref(data), _1, _2);
      commands["COUNT"] = std::bind(getCount, std::cref(data), _1, _2);
      commands["MAX"] = std::bind(getMax, std::cref(data), _1, _2);
      commands["MIN"] = std::bind(getMin, std::cref(data), _1, _2);
      commands["INTERSECTIONS"] = std::bind(getIntersections, std::cref(data), _1, _2);
      commands["ECHO"] = std::bind(getEcho, std::ref(data), _1, _2);
    }
    std::string commandName = "";
    while (std::cin >> commandName)
    {
      try
      {
        commands.at(commandName)(std::cin, std::cout);
        std::cout << "\n";
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
