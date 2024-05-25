#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <cmath>
#include <iomanip>
#include <map>
#include "StreamGuard.hpp"

namespace erfurt
{
  double areaNum(const std::vector<Polygon> & poly, size_t num);
  double areaEven(const std::vector<Polygon> & poly);
  double areaOdd(const std::vector<Polygon> & poly);
  double areaMean(const std::vector<Polygon> & poly);
}

void erfurt::makeArea(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  double result = 0.0;
  std::string arg;
  in >> arg;
  std::map<std::string, std::function<double()>> subcom;
  {
    using namespace std::placeholders;
    subcom["EVEN"] = std::bind(areaEven, poly);
    subcom["ODD"] = std::bind(areaOdd, poly);
    subcom["MEAN"] = std::bind(areaMean, poly);
  }
  try
  {
    size_t num = std::stoull(arg);
    if (num < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    result = areaNum(poly, num);
  }
  catch (const std::invalid_argument&)
  {
    result = subcom[arg]();
  }
  StreamGuard sg(out);
  out << std::fixed;
  out.precision(1);
  out << result << '\n';
}

namespace erfurt
{
  void maxArea(const std::vector< Polygon > & poly, std::ostream & out);
  void maxVertexes(const std::vector< Polygon > & poly, std::ostream & out);
}

void erfurt::makeMax(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  std::map<std::string, std::function<void(std::ostream &)>> subcom;
  {
    using namespace std::placeholders;
    subcom["AREA"] = std::bind(maxArea, poly, _1);
    subcom["VERTEXES"] = std::bind(maxVertexes, poly, _1);
  }
  subcom[arg](out);
  out << '\n';
}

namespace erfurt
{
  void minArea(const std::vector< Polygon > & poly, std::ostream & out);
  void minVertexes(const std::vector< Polygon > & poly, std::ostream & out);
}

void erfurt::makeMin(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  std::map<std::string, std::function<void(std::ostream &)>> subcom;
  {
    using namespace std::placeholders;
    subcom["AREA"] = std::bind(minArea, poly, _1);
    subcom["VERTEXES"] = std::bind(minVertexes, poly, _1);
  }
  subcom[arg](out);
  out << '\n';
}

namespace erfurt
{
  bool isEvenVertexes(const Polygon & poly);
  bool isOddVertexes(const Polygon & poly);
  bool isNumVertexes(const Polygon & poly, size_t num);
}

void erfurt::makeCount(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::string arg;
  in >> arg;
  std::map<std::string, std::function<bool(const Polygon&)>> subcom;
  subcom["EVEN"] = isEvenVertexes;
  subcom["ODD"] = isOddVertexes;
  size_t result = 0;
  try
  {
    size_t num = std::stoull(arg);
    if (num < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    result = std::count_if(poly.cbegin(), poly.cend(), std::bind(isNumVertexes, _1, num));
  }
  catch (const std::invalid_argument&)
  {
    result = std::count_if(poly.cbegin(), poly.cend(), subcom.at(arg));
  }
  out << result << '\n';
}

namespace erfurt
{
  bool isPerm(const Polygon & poly1, const Polygon & poly2);
}

void erfurt::makePerms(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  Polygon fig;
  in >> fig;
  if (!in || fig.points.empty() || in.peek() != '\n')
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto pred = std::bind(isPerm, std::placeholders::_1, fig);
  out << std::count_if(poly.cbegin(), poly.cend(), pred) << '\n';
}

namespace erfurt
{
  bool isIndenticalPoly(const Polygon & poly1, const Polygon & poly2, const Polygon & poly);
}

void erfurt::makeRmecho(std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || polygon.points.empty())
  {
    throw std::invalid_argument("INVALID ARGUMENT");
  }
  auto last = std::unique(poly.begin(), poly.end(),
    std::bind(isIndenticalPoly, std::placeholders::_1, std::placeholders::_2, polygon));
  size_t erased = std::distance(last, poly.end());
  poly.erase(last, poly.end());
  out << erased;
}

double erfurt::areaNum(const std::vector< Polygon > & poly, size_t num)
{
  return detail::getAreaIf(poly, std::bind(isNumVertexes, std::placeholders::_1, num));
}

double erfurt::areaEven(const std::vector< Polygon > & poly)
{
  return detail::getAreaIf(poly, isEvenVertexes);
}

double erfurt::areaOdd(const std::vector< Polygon > & poly)
{
  return detail::getAreaIf(poly, isOddVertexes);
}

double erfurt::areaMean(const std::vector< Polygon > & poly)
{
  if (poly.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  return (getAreaPolygons(poly) / poly.size());
}

namespace erfurt
{
  bool isLessArea(const Polygon & poly1, const Polygon & poly2);
  bool isLessSize(const Polygon & poly1, const Polygon & poly2);
}

void erfurt::maxArea(const std::vector< Polygon > & poly, std::ostream & out)
{
  auto max_elem = std::max_element(poly.cbegin(), poly.cend(), isLessArea);
  if (max_elem == poly.cend())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  StreamGuard sg(out);
  out << std::fixed;
  out.precision(1);
  out << getArea(*max_elem) << '\n';
}

void erfurt::maxVertexes(const std::vector< Polygon > & poly, std::ostream & out)
{
  auto max_elem = std::max_element(poly.cbegin(), poly.cend(), isLessSize);
  if (max_elem == poly.cend())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  out << max_elem->points.size() << '\n';
}

void erfurt::minArea(const std::vector< Polygon > & poly, std::ostream & out)
{
  auto min_elem = std::min_element(poly.cbegin(), poly.cend(), isLessArea);
  if (min_elem == poly.cend())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  StreamGuard sg(out);
  out << std::fixed;
  out.precision(1);
  out << getArea(*min_elem) << '\n';
}

void erfurt::minVertexes(const std::vector< Polygon > & poly, std::ostream & out)
{
  auto min_elem = std::min_element(poly.cbegin(), poly.cend(), isLessSize);
  if (min_elem == poly.cend())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  out << min_elem->points.size() << '\n';
}

bool erfurt::isEvenVertexes(const Polygon & poly)
{
  return (poly.points.size() % 2 == 0);
}

bool erfurt::isOddVertexes(const Polygon & poly)
{
  return !isEvenVertexes(poly);
}

bool erfurt::isNumVertexes(const Polygon & poly, size_t num)
{
  return (poly.points.size() == num);
}

bool erfurt::isLessArea(const Polygon & poly1, const Polygon & poly2)
{
  return (getArea(poly1) < getArea(poly2));
}

bool erfurt::isLessSize(const Polygon & poly1, const Polygon & poly2)
{
  return (poly1.points.size() < poly2.points.size());
}

bool erfurt::isPerm(const Polygon & poly1, const Polygon & poly2)
{
  if (poly1.points.size() != poly2.points.size())
  {
    return false;
  }
  auto pred = std::bind(isPointIn, std::placeholders::_1, poly2);
  return std::distance(poly1.points.cbegin(), poly1.points.cend()) ==
    std::count_if(poly1.points.cbegin(), poly1.points.cend(), pred);
}

bool erfurt::isIndenticalPoly(const Polygon & poly1, const Polygon & poly2, const Polygon & poly)
{
  return isEqual(poly1, poly) && isEqual(poly2, poly);
}
