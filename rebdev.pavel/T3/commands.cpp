#include "commands.hpp"

#include <algorithm>
#include <numeric>
#include <iterator>

#include "triangle.hpp"

void rebdev::areaEven(const polyVec & p, std::istream & in, std::ostream & out)
{

}
void rebdev::areaOdd(const polyVec & p, std::istream & in, std::ostream & out)
{

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

double rebdev::getArea(const Polygon & p)
{
  size_t triangleNum = (p.points.size() - 2);
  std::vector< Triangle > tria(triangleNum);
  std::generate_n(tria.begin(), triangleNum, TriangleGenerator(p));

  double sum = 0;
  return std::accumulate(tria.begin(), tria.end(), sum, plusArea);
}
