#ifndef SHAPES_H
#define SHAPES_H

#include <vector>
#include <iostream>
#include <functional>
#include <numeric>

namespace kazennov
{
  struct Point
  {
    int x;
    int y;
    friend bool operator==(const Point& p, const Point& other)
    {
      return (p.x == other.x && p.y == other.y);
    }
    friend bool operator>(const Point& p, const Point& other)
    {
      return (p.x > other.x && p.y > other.y);
    }
    friend bool operator<(const Point& p, const Point& other)
    {
      return (p.x < other.x && p.y < other.y);
  };
  struct Polygon
  {
    std::vector<Point> points;
  };
  struct TriangleForArea
  {
    Point p1;
    double operator()(double area, const kazennov::Point& p2, const kazennov::Point& p3)
    {
      area += 0.5 * std::abs((p3.y - p1.y) * (p2.x - p1.x) - (p3.x - p1.x) * (p2.y - p1.y));
      p1 = p2;
      return area;
    }
  };

  double PolygonArea(const Polygon& polygon);
  std::istream& operator>>(std::istream& in, Point& point);
  std::ostream& operator<<(std::ostream& out, const Point& point);
  std::istream& operator>>(std::istream& in, Polygon& polygon);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}

#endif
