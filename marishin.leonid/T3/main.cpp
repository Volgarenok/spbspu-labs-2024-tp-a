#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>
#include "polygon.hpp"
#include "command.hpp"

int main(int argc, char* argv[])
{
  using namespace marishin;
  if (argc != 2)
  {
    std::cerr << "Invalid command line arguments\n";
    return 1;
  }
  else
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Unable to open file\n";
      return 1;
    }
    std::vector< Polygon > polygons;
    using input_it_t = std::istream_iterator< Polygon >;
    while (!in.eof())
    {
      std::copy(input_it_t{ in }, input_it_t{}, std::back_inserter(polygons));
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
    {
      using namespace std::placeholders;
      cmds["AREA"] = std::bind(getArea, std::cref(polygons), _1, _2);
      cmds["MAX"] = std::bind(getMax, std::cref(polygons), _1, _2);
      cmds["MIN"] = std::bind(getMin, std::cref(polygons), _1, _2);
      cmds["COUNT"] = std::bind(getCount, std::cref(polygons), _1, _2);
      cmds["RECTS"] = std::bind(getRects, std::cref(polygons), _2);
      cmds["INTERSECTIONS"] = std::bind(getIntersections, std::cref(polygons), _1, _2);
    }

    std::string command;
    std::cout << std::fixed << std::setprecision(1);
    while (std::cin >> command)
    {
      try
      {
        cmds.at(command)(std::cin, std::cout);
        std::cout << '\n';
      }
      catch (...)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
