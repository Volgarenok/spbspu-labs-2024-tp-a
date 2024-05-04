#include "commands.hpp"
#include "additionalCommands.hpp"
#include <string>
#include <iostream>
#include <numeric>
#include <iterator>
#include <functional>
#include <cmath>

void kuznetsov::getArea(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  if (cmd == "EVEN")
  {
    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaEvenOrOdd, false, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::round(area * 10) / 10 << '\n';
  }
  else if (cmd == "ODD")
  {
    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaEvenOrOdd, true, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::round(area * 10) / 10 << '\n';
  }
  else if (cmd == "MEAN")
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("The polygon must contain at least one shape.\n");
    }
    double area = 0.0;
    using namespace std::placeholders;
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, getAreaPolygonForMean);
    out << std::round((area / polygon.size()) * 10) / 10 << '\n';
  }
  else
  {
    int num = std::stoi(cmd);

    if (num < 3)
    {
      throw std::invalid_argument("The entered number of vertices must be greater than 3.");
    }

    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaPolygonForNum, num, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::round(area * 10) / 10 << '\n';
  }
}

void kuznetsov::getMax(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::string cmd;
  in >> cmd;
  if (cmd == "AREA")
  {
    double maxArea = 0.0;
    maxArea = std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, getMaxArea);
    out << std::round(maxArea * 10) / 10 << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    int  vertexes = 0;
    vertexes = std::accumulate(polygon.cbegin(), polygon.cend(), 0, getMaxVertexes);
    out << vertexes << '\n';
  }
}
