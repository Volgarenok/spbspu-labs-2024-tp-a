#include "polygon.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "inguard.hpp"
#include "delimiter.hpp"

std::istream &vojuck::operator>>(std::istream &in, Polygon& poly)
{
  using sep = DelimiterIO;

  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t vertexes = 0;
  in >> vertexes;
  std::vector< Point > temp;
  if (!in || vertexes < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  while (in.peek() != '\n')
  {
    Point newPoint;
    if (!(in >> sep{ '(' } >> newPoint.x >> sep{ ';' } >> newPoint.y >> sep{ ')' }))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    temp.push_back(newPoint);
  }
  if (temp.size() == vertexes)
  {
    poly.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

double vojuck::Polygon::getArea() const
{
  double area = 0.0;
  size_t n = points.size();
  for (size_t i = 0; i < n; ++i)
  {
    size_t j = (i + 1) % n;
    area += (points[i].x + points[j].x) * (points[i].y - points[j].y);
  }
  return std::abs(area) / 2.0;
}

bool vojuck::Point::operator==(const vojuck::Point& point) const
{
  return (x == point.x && y == point.y);
}

bool vojuck::Polygon::operator==(const vojuck::Polygon& poly) const
{
  if (points.size() != poly.points.size()) return 0;
  for (size_t i = 0; i < points.size(); i++)
  {
    if (!(points[i] == poly.points[i])) return 0;
  }
  return 1;
}

bool vojuck::Point::operator<(const Point& point) const
{
  return x < point.x && y < point.y;
}

void vojuck::calculateArea(const std::vector<Polygon>& polygons, const std::string& heading)
{
  double totalArea = 0.0;
  int count = 0;
  if (heading == "0" || heading == "1" || heading == "2")
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  if (heading == "MEAN" && polygons.size() == 0)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  if (heading == "MEAN")
  {
    for (const auto& poly : polygons)
    {
      if (polygons.size() > 0)
      {
        totalArea += poly.vojuck::Polygon::getArea();
        count++;
        continue;
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
        return;
      }
    }
  }
  else if (std::all_of(heading.cbegin(), heading.cend(), [](char c) { return std::isdigit(c); } ) )
  {
    for (const auto& poly : polygons)
    {
      if (poly.points.size() == std::stoull(heading))
      {
        totalArea += poly.vojuck::Polygon::getArea();
        continue;
      }
    }
  }
  else if (heading == "EVEN")
  {
    for (const auto& poly : polygons)
    {
      if (poly.points.size() % 2 == 0)
      {
        totalArea += poly.vojuck::Polygon::getArea();
        continue;
      }
    }
  }
  else if (heading == "ODD")
  {
    for (const auto& poly : polygons)
    {
      if (poly.points.size() % 2 != 0)
      {
        totalArea += poly.vojuck::Polygon::getArea();
        continue;
      }
    }
  }
  std::cout << (heading == "MEAN" ? totalArea / count : totalArea) << "\n";
}

void vojuck::getMax(const std::vector< vojuck::Polygon >& polygons, const std::string& heading)
{
  if (polygons.size() == 0)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  if (heading == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), [](const vojuck::Polygon& poly)
    {
      return poly.vojuck::Polygon::getArea();
    });
    auto maxElement = std::max_element(areas.cbegin(), areas.cend());
    std::cout << *maxElement << "\n";
  }
  else if (heading == "VERTEXES")
  {
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), vertexes.begin(), [](const vojuck::Polygon& poly) { return poly.points.size(); } );
    auto maxElement = std::max_element(vertexes.cbegin(), vertexes.cend());
    std::cout << *maxElement << "\n";
  }
}

void vojuck::getMin(const std::vector< vojuck::Polygon >& polygons, const std::string& heading)
{
  if (polygons.size() == 0)
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  if (heading == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), [](const vojuck::Polygon& poly)
    {
      return poly.vojuck::Polygon::getArea();
    });
    auto minElement = std::min_element(areas.cbegin(), areas.cend());
    std::cout << *minElement << "\n";
  }
  else if (heading == "VERTEXES")
  {
    std::vector< size_t > vertexes(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), vertexes.begin(), [](const vojuck::Polygon& poly) { return poly.points.size(); } );
    auto minElement = std::min_element(vertexes.cbegin(), vertexes.cend());
    std::cout << *minElement << "\n";
  }
}

void vojuck::countPolygons(const std::vector< vojuck::Polygon >& polygons, const std::string& heading)
{
  size_t count = 0;
  if (heading == "EVEN")
  {
    for (const auto& poly : polygons)
    {
      if (poly.points.size() % 2 == 0)
      {
        count++;
      }
    }
  }
  else if (heading == "ODD")
  {
    for (const auto& poly : polygons)
    {
      if (poly.points.size() % 2 != 0)
      {
        count++;
      }
    }
  }
  else if (std::all_of(heading.cbegin(), heading.cend(), [](char c) { return std::isdigit(c); } ) )
  {
    size_t vertexes = std::stoull(heading);
    if (vertexes < 3)
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    for (const auto& poly : polygons)
    {
      if (poly.points.size() == vertexes)
      {
        count++;
      }
    }
  }

  std::cout << count << "\n";
}

double vojuck::getDistance(const Point& point1, const Point& point2)
{
  return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

bool vojuck::Polygon::isRectangle() const
{
  if (points.size() != 4)
  {
    return false;
  }
  double side1 = getDistance(points[0], points[1]);
  double side2 = getDistance(points[1], points[2]);
  double side3 = getDistance(points[2], points[3]);
  double side4 = getDistance(points[3], points[0]);

  double diagonal1 = getDistance(points[0], points[2]);
  double diagonal2 = getDistance(points[1], points[3]);

  return (side1 == side3 && side2 == side4 && diagonal1 == diagonal2);
}

void vojuck::rects(const std::vector< vojuck::Polygon >& polygons)
{
  auto count = std::count_if(polygons.cbegin(), polygons.cend(),[](const Polygon& poly) { return poly.vojuck::Polygon::isRectangle(); } );
  std::cout << count << "\n";
}

void vojuck::maxSeq(const std::vector< vojuck::Polygon >& polygons, std::istream& in)
{
  Polygon element;
  in >> element;
  if (!in || element.points.empty())
  {
    //std::cout << "<INVALID COMMAND>" << "\n";
    return;
  }
  size_t count = 0;
  size_t maxCount = 0;
  for (const auto& poly : polygons)
  {
    if (poly == element)
    {
      count++;
    }
    else
    {
      maxCount = std::max(maxCount, count);
      count = 0;
    }
  }
  maxCount = std::max(maxCount,count);
  std::cout << std::max(maxCount, count) << "\n";
}

bool vojuck::doPolygonsIntersect(const vojuck::Polygon& poly1, const vojuck::Polygon& poly2)
{
  auto rect1 = std::minmax_element(poly1.points.cbegin(), poly1.points.cend());
  auto rect2 = std::minmax_element(poly2.points.cbegin(), poly2.points.cend());
  return !((*rect1.second < *rect2.first) || (*rect2.second < *rect1.first));
}

void vojuck::intersections(const std::vector< vojuck::Polygon >& polygons, std::istream& in)
{
  vojuck::Polygon element;
  in >> element;
  if (!in || element.points.empty())
  {
    //std::cout << "<INVALID COMMAND>\n";
    return;
  }
  auto count = std::count_if(polygons.cbegin(), polygons.cend(), [element](const vojuck::Polygon& poly)
  {
    return vojuck::doPolygonsIntersect(poly, element);
  });
  std::cout << count << "\n";
}
