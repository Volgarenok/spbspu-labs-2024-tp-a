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
    for (int i = 0; i < polygon.size(); ++i)
    {
      area += getAreaEvenOrOdd(polygon[i], false);
    }
    out << area << '\n';
  }
  else if (cmd == "ODD")
  {
    double area = 0.0;
    for (int i = 0; i < polygon.size(); ++i)
    {
      area += getAreaEvenOrOdd(polygon[i], true);
    }
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
