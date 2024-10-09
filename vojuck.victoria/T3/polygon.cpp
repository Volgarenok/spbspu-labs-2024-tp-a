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
  if (vertexes > 2)
  {
    while (in.peek() != '\n')
    {
      Point newPoint;
      in >> sep{ '(' } >> newPoint.x >> sep{ ';' } >> newPoint.y >> sep{ ')' };
      temp.push_back(newPoint);
    }
    if (temp.size() == vertexes)
    {
      poly.points = temp;
    }
    else
    {
      std::cerr << "Wrong\n";
      return in;
    }
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
//1
void vojuck::calculateArea(const std::vector<Polygon>& polygons, const std::string& heading)
{
  double totalArea = 0.0;
  int count = 0;
  if (heading == "0" || heading == "1" || heading == "2")
  {
    std::cerr << "<INVALID COMMAND>";
    return;
  }
  if (heading == "MEAN" && polygons.size() == 0)
  {
    std::cerr << "<INVALID COMMAND>";
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
        std::cerr << "<INVALID COMMAND>";
        return;
      }
    }
  }
  else if (std::all_of(heading.cbegin(), heading.cend(), [](char c) { return std::isdigit(c); }))
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
  if (heading == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), [](const vojuck::Polygon& poly) { return poly.vojuck::Polygon::getArea(); });
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
  if (heading == "AREA")
  {
    std::vector< double > areas(polygons.size());
    std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), [](const vojuck::Polygon& poly) { return poly.vojuck::Polygon::getArea(); });
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
