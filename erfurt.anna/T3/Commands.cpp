#include "Commands.hpp"
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <string>
#include <cmath>
#include <iomanip>
#include <map>
#include "Utilies.hpp"
#include "StreamGuard.hpp"

void erfurt::makeArea(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  double result = 0.0;
  std::string arg;
  in >> arg;
  std::map< std::string, std::function< double() > > subcom;
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
  catch (const std::invalid_argument &)
  {
    result = subcom[arg]();
  }
  StreamGuard sg(out);
  out << std::fixed;
  out.precision(1);
  out << result;
}

void erfurt::makeMax(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  std::map< std::string, std::function< void(std::ostream &) > > subcom;
  {
    using namespace std::placeholders;
    subcom["AREA"] = std::bind(maxArea, poly, _1);
    subcom["VERTEXES"] = std::bind(maxVertexes, poly, _1);
  }
  subcom[arg](out);
}

void erfurt::makeMin(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  std::string arg;
  in >> arg;
  std::map< std::string, std::function< void(std::ostream &) > > subcom;
  {
    using namespace std::placeholders;
    subcom["AREA"] = std::bind(minArea, poly, _1);
    subcom["VERTEXES"] = std::bind(minVertexes, poly, _1);
  }
  subcom[arg](out);
}

void erfurt::makeCount(const std::vector< Polygon > & poly, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  std::string arg;
  in >> arg;
  std::map< std::string, std::function< bool(const Polygon&) > > subcom;
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
  catch (const std::invalid_argument &)
  {
    result = std::count_if(poly.cbegin(), poly.cend(), subcom.at(arg));
  }
  out << result;
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
  out << std::count_if(poly.cbegin(), poly.cend(), pred);
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
