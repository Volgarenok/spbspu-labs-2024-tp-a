#include "polygon.hpp"
#include <delimeter.hpp>
#include <iterator>
#include <algorithm>

std::istream & namestnikov::operator>>(std::istream & in, namestnikov::Point & point)
{
  using delC = DelimeterChar;
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  Point tempPoint = {0, 0};
  in >> delC{'('} >> tempPoint.x >> delC{';'} >> tempPoint.y >> delC{')'};
  if (in)
  {
    point = tempPoint;
  }
  return in;
}

std::ostream & namestnikov::operator<<(std::ostream & out, const namestnikov::Point & point)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}

double namestnikov::Polygon::getArea() const
{

}

double namestnikov::PolygonArea::operator()(double area, const namestnikov::Point & second)
{
  area += 0.5 * std::abs((third.y - first.y) * (second.x - first.x) - (third.x - first.x) * (second.y - first.y));
  first = second;
  return area;
}

std::istream & namestnikov::operator>>(std::istream & in, namestnikov::Polygon & polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t pointsCount = 0;
  in >> pointsCount;
  if (pointsCount < 3)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    std::vector< Point > tempPolygon;
    using input_iterator_t = std::istream_iterator< Point >;
    std::copy_n(input_iterator_t{in}, pointsCount, std::back_inserter(tempPolygon));
    if (in)
    {
      polygon.points = tempPolygon;
    }
  }
  return in;
}

std::ostream & namestnikov::operator<<(std::ostream & out, const namestnikov::Polygon & polygon)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  using output_iterator_t = std::ostream_iterator< Point >;
  out << polygon.points.size() << " ";
  std::copy(polygon.points.cbegin(), polygon.points.cend(), output_iterator_t{out, " "});
  return out;
}