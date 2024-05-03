#include "commands.hpp"
#include <functional>
#include <numeric>

double getAreaEvenOdd(double curr, const piyavkin::Polygon& pol, bool even)
{
  if (even && pol.points.size() % 2 != 0)
  {
    curr += pol.getArea();
  }
  else if (!even && pol.points.size() % 2 == 0)
  {
    curr += pol.getArea();
  }
  return curr;
}

void piyavkin::getArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol)
{
  std::string name = "";
  in >> name;
  double sum = 0;
  using namespace std::placeholders;
  if (name == "EVEN")
  {
    sum = std::accumulate(pol.begin(), pol.end(), 0.0, std::bind(getAreaEvenOdd, _1, _2, true));
  }
  else if (name == "ODD")
  {
    sum = std::accumulate(pol.begin(), pol.end(), 0.0, std::bind(getAreaEvenOdd, _1, _2, false));
  }
  out << sum << '\n';
}