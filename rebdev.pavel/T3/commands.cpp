#include "commands.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <limits>
#include <cmath>
#include <stdexcept>

#include "baseForCommands.hpp"

void rebdev::areaEven(const polyVec & p, std::ostream & out)
{
  double area = rebdev_private::areaIf(p,
    [](const Polygon & polygon)
    {
      return ((polygon.points.size() % 2) != 0);
    });

  out << area << '\n';
}
void rebdev::areaOdd(const polyVec & p, std::ostream & out)
{
  double area = rebdev_private::areaIf(p,
    [](const Polygon & polygon)
    {
      return ((polygon.points.size() % 2) == 0);
    });

  out << area << '\n';
}
void rebdev::areaMean(const polyVec & p, std::ostream & out)
{
  if (p.empty())
  {
    throw std::logic_error("Empty file!");
  }
  double area = 0;
  area = std::accumulate(p.begin(), p.end(), area, rebdev_private::getArea);

  out << (area / p.size()) << '\n';
}
void rebdev::areaNum(size_t s, const polyVec & p, std::ostream & out)
{
  if (s < 3)
  {
    throw std::logic_error("Bad vertex num!");
  }
  double area = rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      return (polygon.points.size() != s);
    });

  out << area << '\n';
}
void rebdev::maxArea(const polyVec & p, std::ostream & out)
{
  if (p.empty())
  {
    throw std::logic_error("Empty file!");
  }
  std::vector< double > areaVec(p.size());
  rebdev_private::fillAreaVec(p, areaVec);
  out << *std::max_element(areaVec.begin(), areaVec.end()) << '\n';
}
void rebdev::maxVertexes(const polyVec & p, std::ostream & out)
{
  if (p.empty())
  {
    throw std::logic_error("Empty file!");
  }
  std::vector< size_t > vertVec(p.size());
  rebdev_private::fillVertVec(p, vertVec);
  out <<  *std::max_element(vertVec.begin(), vertVec.end()) << '\n';
}
void rebdev::minArea(const polyVec & p, std::ostream & out)
{
  if (p.empty())
  {
    throw std::logic_error("Bad count num!");
  }
  std::vector< double > areaVec(p.size());
  rebdev_private::fillAreaVec(p, areaVec);
  out << *std::min_element(areaVec.begin(), areaVec.end()) << '\n';
}
void rebdev::minVertexes(const polyVec & p, std::ostream & out)
{
  if (p.empty())
  {
    throw std::logic_error("Empty file!");
  }
  std::vector< size_t > vertVec(p.size());
  rebdev_private::fillVertVec(p, vertVec);
  out << *std::min_element(vertVec.begin(), vertVec.end()) << '\n';
}
void rebdev::countEven(const polyVec & p, std::ostream & out)
{
  size_t NumOfCountEven = std::count_if(p.begin(), p.end(),
    [](const Polygon & polygon)
    {
      return (((polygon.points.size() % 2) == 0) && (!polygon.points.empty()));
    });
  out << NumOfCountEven << '\n';
}
void rebdev::countOdd(const polyVec & p, std::ostream & out)
{
  size_t NumOfCountOdd = std::count_if(p.begin(), p.end(),
    [](const Polygon & polygon)
    {
      return ((polygon.points.size() % 2) != 0);
    });
  out << NumOfCountOdd << '\n';
}
void rebdev::countNum(size_t s, const polyVec & p, std::ostream & out)
{
  if (s < 3)
  {
    throw std::logic_error("Bad vertex num!");
  }
  size_t NumOfCountNum = std::count_if(p.begin(), p.end(),
    [&](const Polygon & polygon)
    {
      return (polygon.points.size() == s);
    });

  out << NumOfCountNum << '\n';
}
void rebdev::rects(const polyVec & p, std::ostream & out)
{
  size_t rectsNum = std::count_if(p.begin(), p.end(),
    [&](const Polygon & polygon)
    {
      if (polygon.points.size() != 4)
      {
        return false;
      }
      double firstDiagonal = rebdev_private::distanceBetweenPoints(polygon.points[0], polygon.points[2]);
      double secondDiagonal = rebdev_private::distanceBetweenPoints(polygon.points[1], polygon.points[3]);
      return (firstDiagonal == secondDiagonal);
    });
  out << rectsNum << '\n';
}
void rebdev::inframe(const polyVec & p, std::istream & in, std::ostream & out)
{
  Polygon inPoly;
  in >> inPoly;
  if (inPoly.points.empty())
  {
    throw std::invalid_argument("Bad polygon input");
  }
  int xMax = std::numeric_limits< int >::min();
  int yMax = std::numeric_limits< int >::min();
  int xMin = std::numeric_limits< int >::max();
  int yMin = std::numeric_limits< int >::max();
  std::for_each(p.begin(), p.end(),
    [&](const Polygon & polygon)
    {
      std::for_each(polygon.points.begin(), polygon.points.end(),
        [&](const Point & point)
        {
          xMax = std::max(xMax, point.x);
          yMax = std::max(yMax, point.y);
          xMin = std::min(xMin, point.x);
          yMin = std::min(yMin, point.y);
        });
    });
  bool inFrame = true;
  std::for_each(inPoly.points.begin(), inPoly.points.end(),
    [&](const Point & point)
    {
      if ((point.x > xMax) || (point.x < xMin) || (point.y > yMax) || (point.y < yMin))
      {
        inFrame = false;
      }
    });
  out << '<' << ((inFrame == true) ? "TRUE" : "FALSE") << ">\n";
}
