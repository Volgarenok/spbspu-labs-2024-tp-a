#include "commands.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>
#include <limits>
#include <cmath>

#include "baseForCommands.hpp"

void rebdev::areaEven(const polyVec & p, std::ostream & out)
{
  double area = rebdev_private::areaIf(p,
    [](const Polygon & polygon)
    {
      return ((polygon.points.size() % 2) != 0);
    });

  out << "AREA EVEN\n";
  out << area << '\n';
}
void rebdev::areaOdd(const polyVec & p, std::ostream & out)
{
  double area = rebdev_private::areaIf(p,
    [](const Polygon & polygon)
    {
      return ((polygon.points.size() % 2) == 0);
    });

  out << "AREA ODD\n";
  out << area << '\n';
}
void rebdev::areaMean(const polyVec & p, std::ostream & out)
{
  double area = rebdev_private::areaIf(p,
    [](const Polygon & polygon)
    {
      return false;
    });

  out << "AREA MEAN\n";
  out << (area / p.size()) << '\n';
}
void rebdev::areaNum(size_t s, const polyVec & p, std::ostream & out)
{
  double area = rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      return (polygon.points.size() != s);
    });

  out << "AREA " << s << '\n';
  out << area << '\n';
}
void rebdev::maxArea(const polyVec & p, std::ostream & out)
{
  double maxArea = std::numeric_limits< double >::min();
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      maxArea = std::max(maxArea, rebdev_private::getArea(0, polygon));
      return false;
    });

  out << "MAX AREA\n";
  out << maxArea << '\n';
}
void rebdev::maxVertexes(const polyVec & p, std::ostream & out)
{
  size_t maxVertexes = std::numeric_limits< size_t >::min();
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      maxVertexes = std::max(maxVertexes, polygon.points.size());
      return false;
    });

  out << "MAX VERTEXES\n";
  out << maxVertexes << '\n';
}
void rebdev::minArea(const polyVec & p, std::ostream & out)
{
  double minArea = std::numeric_limits< double >::max();
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      minArea = std::min(minArea, rebdev_private::getArea(0, polygon));
      return false;
    });

  out << "MIN AREA\n";
  out << minArea << '\n';
}
void rebdev::minVertexes(const polyVec & p, std::ostream & out)
{
  size_t minVertexes = std::numeric_limits< size_t >::max();
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      minVertexes = std::min(minVertexes, polygon.points.size());
      return false;
    });

  out << "MIN VERTEXES\n";
  out << minVertexes << '\n';
}
void rebdev::countEven(const polyVec & p, std::ostream & out)
{
  size_t NumOfCountEven = 0;
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      if ((polygon.points.size() % 2) == 0)
      {
        ++NumOfCountEven;
      }
      return false;
    });

  out << "COUNT EVEN\n";
  out << NumOfCountEven << '\n';
}
void rebdev::countOdd(const polyVec & p, std::ostream & out)
{
  size_t NumOfCountOdd = 0;
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      if ((polygon.points.size() % 2) != 0)
      {
        ++NumOfCountOdd;
      }
      return false;
    });

  out << "COUNT ODD\n";
  out << NumOfCountOdd << '\n';
}
void rebdev::countNum(size_t s, const polyVec & p, std::ostream & out)
{
  size_t NumOfCountNum = 0;
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      if (polygon.points.size() == s)
      {
        ++NumOfCountNum;
      }
      return false;
    });

  out << "COUNT " << s << '\n';
  out << NumOfCountNum << '\n';
}
void rebdev::rects(const polyVec & p, std::ostream & out)
{
  size_t rectsNum = 0;
  rebdev_private::areaIf(p,
    [&](const Polygon & polygon)
    {
      if (polygon.points.size() == 4)
      {
        double firstDiagonal = std::pow((polygon.points[0].x - polygon.points[2].x), 2);
        firstDiagonal += std::pow((polygon.points[0].y - polygon.points[2].y), 2);
        firstDiagonal = std::sqrt(firstDiagonal);

        double secondDiagonal = std::pow((polygon.points[1].x - polygon.points[3].x), 2);
        secondDiagonal += std::pow((polygon.points[1].y - polygon.points[3].y), 2);
        secondDiagonal = std::sqrt(secondDiagonal);

        if (firstDiagonal == secondDiagonal)
        {
          ++rectsNum;
        }
      }
      return false;
    });

  out << "RECTS \n";
  out << rectsNum << '\n';
}
void rebdev::inframe(const polyVec & p, std::istream & in, std::ostream & out)
{
  size_t i = p.size();//delete after test
  in >> i;
  out << i;
}
