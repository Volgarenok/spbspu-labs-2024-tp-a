#include "commands.hpp"
#include <iostream>
#include <numeric>
#include <iterator>
#include <functional>

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
    out << area << '\n';
  }
  else if (cmd == "ODD")
  {
    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaEvenOrOdd, true, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << area << '\n';
  }
  else if (cmd == "MEAN")
  {
    out << "ODD\n";
  }
  else
  {
    out << "num\n";
  }
}
