#include <cmath>
#include <algorithm>
#include <functional>
#include <iomanip>
#include "IOFormatGuard.h"
#include "ReadIO.h"
#include "Commands.h"

namespace serter
{
  double getArea(const Polygon& polygon)
  {
    double res = 0.0;
    for (size_t i = 0; i < polygon.points.size() - 1; ++i)
    {
      res += 0.5 * (polygon.points[i].x * polygon.points[i + 1].y - polygon.points[i + 1].x * polygon.points[i].y);
    }
    res += 0.5 * (polygon.points.back().x * polygon.points.front().y - polygon.points.front().x * polygon.points.back().y);
    return std::abs(res);
  }

  bool isLessByArea(const Polygon& lhs, const Polygon& rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool isEqualPolygon(const Polygon& lhs, const Polygon& rhs, const Polygon& polygon)
  {
    return (rhs.points == lhs.points) && (rhs.points == polygon.points);
  }

  bool operator==(const Polygon& one, const Polygon& two)
  {
    return one.points == two.points;
  }
}

void serter::echo(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon polygon;
  input >> polygon;
  if (!input)
  {
    throw std::runtime_error("Invalid polygon.");
  }

  size_t sameCount = std::count(polygons.begin(), polygons.end(), polygon);
  std::vector< Polygon > temp;

  for (const auto& figure : polygons)
  {
    temp.push_back(figure);
    if (figure == polygon)
    {
      temp.push_back(polygon);
    }
  }

  polygons = temp;
  output << sameCount << '\n';
}

void serter::rmEcho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon poly;
  input >> poly;
  if (!input)
  {
    throw std::runtime_error("Invalid polygon.");
  }

  auto pred = std::bind(isEqualPolygon, std::placeholders::_1, std::placeholders::_2, poly);
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

  if (!input)
  {
    throw std::runtime_error("Invalid polygon.");
  }

  output << std::count_if(std::begin(polygons), std::end(polygons), 
              std::bind(isLessByArea, std::placeholders::_1, poly)) << '\n';
}

