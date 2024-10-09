#include "polygon.hpp"

double vojuck::Polygon::getArea()
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

double calculateArea(const std::vector<Polygon>& polygons, const std::string& heading)
{
  double totalArea = 0.0;
  if (heading == "0" || heading == "1" || heading == "2")
  {
    std::cerr << "<INVALID COMMAND>";
    return;
  }
  if (heading == "MEAN" && polygons.size() == 0)
  {
    std::cerr << "<INVALID COMMAND>";
    return 1;
  }
  if (heading == "MEAN")
  {
    int count = 0;
    for (const auto& poly : polygons)
    {
      if (polygons.size() > 0)
      {
        totalArea += poly.getArea();
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
        totalArea += poly.getArea();
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
        totalArea += poly.getArea();
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
        totalArea += poly.getArea();
        continue;
      }
    }
  }
  return (heading == "MEAN" ? totalArea / count : totalArea) << "\n";
}
