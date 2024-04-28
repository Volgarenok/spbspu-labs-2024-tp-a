#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include <vector>

#include "shapes.hpp"

namespace babinov
{
  void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void rects(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void intersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

int main(int, char* argv[])
{
  using namespace babinov;
  using input_it_t = std::istream_iterator< Polygon >;

  char* fileName = argv[1];
  std::ifstream file(fileName);
  std::vector< Polygon > polygons{input_it_t(file), input_it_t()};
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
    cmds["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
    cmds["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
    cmds["RECTS"] = std::bind(rects, std::cref(polygons), _1, _2);
    cmds["INTERSECTIONS"] = std::bind(intersections, std::cref(polygons), _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
