#include <cmath>
#include <algorithm>
#include <functional>
#include <iomanip>
#include "IOFormatGuard.hpp"
#include "ReadIO.hpp"
#include "Commands.hpp"

namespace serter
{
  bool isSize(const Polygon& polygon, size_t points)
  {
    return polygon.points.size() == points;
  }

  bool isCurrVertexes(size_t vertexes, const Polygon& polygon)
  {
    return polygon.points.size() == vertexes;
  }

  bool isEven(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  double getArea(const Polygon& polygon)
  {
    double res = 0.0;
    for (size_t i = 0; i < polygon.points.size() - 1; ++i)
    {
      res += 0.5 * (polygon.points[i].x * polygon.points[i + 1].y - polygon.points[i + 1].x * polygon.points[i].y);;
    }
    res += 0.5 * (polygon.points.back().x * polygon.points.front().y - polygon.points.front().x * polygon.points.back().y);
    return std::abs(res);
  }

  bool compareSize(const Polygon& lhs, const Polygon& rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  bool compareArea(const Polygon& lhs, const Polygon& rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  double calcAreaMean(size_t polygons, const Polygon& polygon)
  {
    return getArea(polygon) / polygons;
  }

  bool isLessByArea(const Polygon& lhs, const Polygon& rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool isEqualPolygon(const Polygon& lhs, const Polygon& rhs, const Polygon& polygon)
  {
    return (rhs.points == lhs.points) && (rhs.points == polygon.points);
  }

  bool operator==(const Polygon& lhs, const Polygon& rhs)
  {
    return lhs.points == rhs.points;
  }
}

void serter::area(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  std::vector< Polygon > polygonsToCount;
  std::function< double(const Polygon&) >
    func = getArea;
  if (arg == "EVEN")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), isEven);
  }
  else if (arg == "ODD")
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), isOdd);
  }
  else if (arg == "MEAN")
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid arg");
    }
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount));
    func = std::bind(calcAreaMean, polygons.size(), std::placeholders::_1);
  }
  else
  {
    size_t vertexes = std::stoull(arg);
    if (vertexes < 3)
    {
      throw std::invalid_argument("Invalid arg");
    }
    auto vertexPred = std::bind(isCurrVertexes, vertexes, std::placeholders::_1);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), vertexPred);
  }
  std::vector< double > areas;
  std::transform(polygonsToCount.cbegin(), polygonsToCount.cend(), std::back_inserter(areas), func);
  IOFormatGuard guard(output);
  output << std::setprecision(1) << std::fixed;
  output << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << '\n';
}

void serter::min(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  if (!polygons.empty() && arg == "AREA")
  {
    IOFormatGuard guard(output);
    output << std::fixed << std::setprecision(1);
    output << getArea(*(std::min_element(polygons.begin(), polygons.end(), compareArea))) << '\n';
  }
  if (!polygons.empty() && arg == "VERTEXES")
  {
    output << std::min_element(polygons.begin(), polygons.end(), compareSize)->points.size() << '\n';
  }
  throw std::invalid_argument("Invalid arg");
}

void serter::max(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  if (!polygons.empty() && arg == "AREA")
  {
    IOFormatGuard guard(output);
    output << std::fixed << std::setprecision(1);
    output << getArea(*(std::max_element(polygons.begin(), polygons.end(), compareArea))) << '\n';
  }
  else if (!polygons.empty() && arg == "VERTEXES")
  {
    output << std::max_element(polygons.begin(), polygons.end(), compareSize)->points.size() << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid arg");
  }
}

void serter::count(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;

  if (arg == "ODD")
  {
    output << std::count_if(polygons.cbegin(), polygons.cend(), isOdd) << '\n';
  }
  else if (arg == "EVEN")
  {
    output << std::count_if(polygons.cbegin(), polygons.cend(), isEven) << '\n';
  }
  else if (std::all_of(arg.cbegin(), arg.cend(), ::isdigit))
  {
    size_t vertexesNum = stoull(arg);
    if (vertexesNum < 3)
    {
      throw std::logic_error("Invalid arg");
    }
    std::function< bool(const Polygon&) >
      pred = std::bind(isSize, std::placeholders::_1, vertexesNum);
    output << std::count_if(polygons.cbegin(), polygons.cend(), pred) << '\n';
  }
  else
  {
    throw std::logic_error("Invalid arg");
  }
}

void serter::echo(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon polygon;
  input >> polygon;
  if (!input || input.peek() != '\n')
  {
    throw std::invalid_argument("Invalid arg");
  }
  size_t countEcho = std::count(polygons.begin(), polygons.end(), polygon);
  std::vector< Polygon > temp(polygons.size() + countEcho);
  size_t sameCount = 0;
  for (const auto& figure : polygons)
  {
    temp.push_back(figure);
    if (figure == polygon)
    {
      ++sameCount;
      temp.push_back(polygon);
    }
  }
  polygons = temp;
  output << sameCount << '\n';
}

void serter::rmEcho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  Polygon poly;
  input >> poly;
  if (!input || input.peek() != '\n')
  {
    throw std::invalid_argument("Invalid arg");
  }
  auto pred = std::bind(isEqualPolygon, _1, _2, poly);
  auto new_end = std::unique(polygons.begin(), polygons.end(), pred);
  size_t res = std::distance(new_end, polygons.end());
  polygons.erase(new_end, polygons.end());
  IOFormatGuard iofmtguard(output);
  output << std::fixed << std::setprecision(1);
  output << res << "\n";
}

void serter::lessArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon poly;
  input >> poly;
  if (!input || input.peek() != '\n')
  {
    throw std::invalid_argument("Invalid arg");
  }
  using namespace std::placeholders;
  output << std::count_if(std::begin(polygons), std::end(polygons), std::bind(isLessByArea, _1, poly)) << '\n';
}

