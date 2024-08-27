#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <delimeter.hpp>

std::istream & ishmuratov::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  Point temp = {0, 0};
  input >> Delimeter{'('} >> temp.x >> Delimeter{';'} >> temp.y >> Delimeter{')'};
  if (input)
  {
    point = temp;
  }
  return input;
}

double ishmuratov::get_area(const Polygon & poly)
{
  return calculate_area(poly.points.cbegin(), poly.points.cend(), poly.points.cbegin(), ++poly.points.cbegin(), 0);
}

double ishmuratov::calculate_area(point_it begin, point_it end, point_it p1, point_it p2, double curr)
{
  if (p2 == end)
  {
    return 0.5 * std::abs(curr + calculate_pair(*p1, *begin));
  }
  curr += calculate_pair(*p1, *p2);
  return calculate_area(begin, end, ++p1, ++p2, curr);
}

double ishmuratov::calculate_pair(const Point &p1, const Point &p2)
{
  return p1.x * p2.y - p2.x * p1.y;
}

std::istream & ishmuratov::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  size_t points_num = 0;
  input >> points_num;
  std::vector< Point > temp;
  using input_it_t = std::istream_iterator< Point >;
  std::copy_n(input_it_t{ input }, points_num, std::back_inserter(temp));
  if (temp.size() == points_num)
  {
    polygon.points = temp;
  }
  return input;
}

bool ishmuratov::operator==(const Point & p1, const Point & p2)
{
  return (p1.x == p2.x) && (p1.y == p2.y);
}

bool ishmuratov::operator==(const Polygon & poly1, const Polygon & poly2)
{
  return poly1.points == poly2.points;
}
