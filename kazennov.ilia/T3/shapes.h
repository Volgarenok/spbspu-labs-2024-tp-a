#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <iostream>

namespace kazennov
{
  struct Point
  {
    int x;
    int y;
    friend bool operator==(const Point& p, const Point& other)
    {
      if (p.x == other.x && p.y == other.y)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    friend bool operator>(const Point& p, const Point& other)
    {
      if (p.x > other.x && p.y > other.y)
      {
	return true;
      }
      return false;
    }
    friend bool operator<(const Point& p, const Point& other)
    {
      if (p.x < other.x && p.y < other.y)
      {
	return true;
      }
      return false;
    }

  };

  struct Polygon
  {
    std::vector<Point> points;
  };

  struct TriangleForArea
  {
    kazennov::Point p1;
    double operator()(double area, const kazennov::Point& p2, const kazennov::Point& p3)
    {
      area += 0.5 * std::abs((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y));
      p1 = p2;
      return area;
    }
  };


  double PolygonArea(const Polygon polygon)
  {
    using namespace std::placeholders;
    auto areaCounter = std::bind(TriangleForArea{ polygon.points[1] }, _1, _2, polygon.points[0]);
    return std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0.0, areaCounter);
  }

  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}
#endif
