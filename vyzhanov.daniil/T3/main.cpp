#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <iterator>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char** argv)
{
  using namespace vyzhanov;
  if (argc != 2)
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }

  std::ifstream input_file(argv[1]);
  std::vector< Polygon > polygons;
  std::string args;

  if (!input_file.is_open())
  {
    std::cerr << "Invalid file name\n";
    return 1;
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
    commands["LESSAREA"] = std::bind(lessarea, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(rmecho, std::ref(polygons), _1, _2);
    commands["RECTS"] = std::bind(rects, std::cref(polygons), _1, _2);
  }
  while (!input_file.eof())
  {
    std::copy(std::istream_iterator< Polygon >{ input_file },
      std::istream_iterator< Polygon >{}, std::back_inserter(polygons));
    if (input_file.fail())
    {
      input_file.clear();
      input_file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  while (std::cin >> args)
  {
    try
    {
      commands.at(args)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
