#include "polygon.hpp"
#include <algorithm>
#include <iterator>
#include <delimiter.hpp>

namespace grechishnikov
{
  class inputPointIterator: public std::iterator< std::input_iterator_tag, Point >
  {
  public:
    inputPointIterator(std::istream& in):
      srteam(in),
      point()
    {}
    inputPointIterator& operator++()
    {
      return *this;
    }
    Point& operator*()
    {
      if (srteam.peek() != ' ')
      {
        srteam.setstate(std::ios::failbit);
        return point;
      }
      srteam >> point;
      return point;
    }
  private:
    std::istream& srteam;
    Point point;
  };
}

std::istream& grechishnikov::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = Delimiter;
  in >> del{ '(' } >> point.x >> del{ ';' } >> point.y >> del{ ')' };
  if (!in)
  {
    point = { 0, 0 };
    in.setstate(std::ios::failbit);
  }
  return in;
}

bool grechishnikov::operator<(const Point& lhs, const Point& rhs)
{
  if (lhs.x == rhs.x)
  {
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}

bool grechishnikov::operator==(const Point& lhs, const Point& rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

std::istream& grechishnikov::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t size = 0;
  in >> size;
  if (!in || size < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > temp;
  std::copy_n(inputPointIterator(in), size, std::back_inserter(temp));
  if (!in || in.peek() != '\n')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  polygon.points = temp;
  return in;
}
