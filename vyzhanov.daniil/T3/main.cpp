#include <iostream>
#include <functional>
#include <map>
#include <limits>
#include <fstream>
#include <iterator>
#include <iomanip>
#include "polygon.hpp"
#include "commands.hpp"


int main(int argc, char* argv[])
{
  using namespace vyzhanov;
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }
  std::ifstream input_file(argv[1]);
  std::vector< Polygon > polygons;
  while (!input_file.eof())
  {
    std::copy(std::istream_iterator< Polygon >{ input_file }, std::istream_iterator< Polygon >{}, std::back_inserter(polygons));
    input_file.clear();
    input_file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(area, std::ref(polygons), _1, _2);
    commands["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
    commands["LESSAREA"] = std::bind(lessarea, std::cref(polygons), _1, _2);
    commands["RMECHO"] = std::bind(rmecho, std::ref(polygons), _1, _2);
    commands["RECTS"] = std::bind(rects, std::cref(polygons), _1, _2);
  }
  std::string arg;
  std::cout << std::fixed << std::setprecision(1);
  while (std::cin >> arg)
  {
    try
    {
      commands.at(arg)(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
