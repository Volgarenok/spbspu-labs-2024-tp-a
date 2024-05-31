#include <algorithm>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <vector>

#include "shapes.hpp"

namespace babinov
{
  void execCmdArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void execCmdMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void execCmdMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void execCmdCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void execCmdRects(const std::vector< Polygon >& polygons, std::ostream& out);
  void execCmdIntersections(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
}

bool isValidPolygon(const babinov::Polygon& polygon)
{
  return !polygon.points.empty();
}

int main(int argc, char* argv[])
{
  using namespace babinov;
  using input_it_t = std::istream_iterator< Polygon >;

  if (argc != 2)
  {
    std::cerr << "ERROR: Invalid parameters" << '\n';
    return 1;
  }

  std::ifstream file(argv[1]);
  std::vector< Polygon > polygons;
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy_if(input_it_t{file}, input_it_t{}, std::back_inserter(polygons), isValidPolygon);
  }

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(execCmdArea, std::cref(polygons), _1, _2);
    cmds["MAX"] = std::bind(execCmdMax, std::cref(polygons), _1, _2);
    cmds["MIN"] = std::bind(execCmdMin, std::cref(polygons), _1, _2);
    cmds["COUNT"] = std::bind(execCmdCount, std::cref(polygons), _1, _2);
    cmds["RECTS"] = std::bind(execCmdRects, std::cref(polygons), _2);
    cmds["INTERSECTIONS"] = std::bind(execCmdIntersections, std::cref(polygons), _1, _2);
  }
  std::string cmd;
  std::cout << std::fixed << std::setprecision(1);
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
