#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
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

bool isValidPolygon(const babinov::Polygon& polygon)
{
  return !polygon.points.empty();
}

void clearStream(std::istream& in)
{
  if (in.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

int main(int argc, char* argv[])
{
  using namespace babinov;
  using input_it_t = std::istream_iterator< Polygon >;

  if (argc < 2)
  {
    std::cerr << "ERROR: File name must be passed" << '\n';
    return -1;
  }

  char* fileName = argv[1];
  std::ifstream file(fileName);
  std::vector< Polygon > polygons;
  std::copy_if(input_it_t(file), input_it_t(), std::back_inserter(polygons), isValidPolygon);
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
  std::cout << std::fixed << std::setprecision(1);
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cin.setstate(std::ios::failbit);
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    clearStream(std::cin);
  }
  return 0;
}
