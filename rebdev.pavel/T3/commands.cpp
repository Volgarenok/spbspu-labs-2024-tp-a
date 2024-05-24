#include "commands.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>

#include "baseForCommands.hpp"

void rebdev::areaEven(const polyVec & p, std::istream & in, std::ostream & out)
{
  double area = rebdev_private::areaEvenOddBase(p,
    [](const Polygon & polygon)
    {
      return ((polygon.points.size() % 2) != 0);
    });

  out << "AREA EVEN\n";
  out << area << '\n';
}
void rebdev::areaOdd(const polyVec & p, std::istream & in, std::ostream & out)
{
  double area = rebdev_private::areaEvenOddBase(p,
    [](const Polygon & polygon)
    {
      return ((polygon.points.size() % 2) == 0);
    });

  out << "AREA ODD\n";
  out << area << '\n';
}
void rebdev::areaMean(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::areaNum(size_t s, const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::maxArea(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::maxVertexes(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::minArea(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::minVertexes(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::countEven(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::countOdd(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::countNum(size_t s, const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::rects(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::inframe(const polyVec & p, std::istream & in, std::ostream & out)
{

}
