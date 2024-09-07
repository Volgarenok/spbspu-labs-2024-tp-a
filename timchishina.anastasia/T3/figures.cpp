#include "figures.hpp"
#include <delimiter.hpp>
std::istream& timchishina::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  Point temp{0, 0};
  in >> del{'('} >> temp.x >> del{';'} >> temp.y >> del{')'};
  if (in)
  {
    point = temp;
  }
  return in;
}

std::istream& timchishina::operator>>(std::istream& in, Polygon& poly)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t vertexes = 0;
  in >> vertexes;
  if (vertexes < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  using inIterator = std::istream_iterator< Point >;
  std::copy_n(inIterator{in}, vertexes, std::back_inserter(temp));
  if (in && temp.size() == vertexes)
  {
    poly.points = temp;
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
