#include <cmath>
#include <exception>
#include <functional>
#include <algorithm>
#include <numeric>

#include "commands.hpp"

double kornienko::evenOrOdd(const kornienko::Polygon & polygon, bool isEven)
{
  if (polygon.points.size() % 2 == isEven)
  {
    return 0;
  }
  else
  {
    return polygon.getArea();
  }
}

void kornienko::area(std::istream & in, std::ostream & out, const std::vector< Polygon > polygons)
{
  std::string context;
  in >> context;
  std::function< double(const kornienko::Polygon &) > func;
  using namespace std::placeholders;
  if (context == "EVEN")
  {
    func = std::bind(evenOrOdd, _1, true);
  }
  else if (context == "ODD")
  {
    func = std::bind(evenOrOdd, _1, false);
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>\n");
  }
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), func);
  out << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << "\n";
}
