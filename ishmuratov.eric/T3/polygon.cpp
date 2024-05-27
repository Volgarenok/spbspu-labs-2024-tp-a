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

double ishmuratov::Polygon::get_area()
{
  return calculate_area(points.cbegin(), ++points.cbegin(), 0);
}

double ishmuratov::Polygon::calculate_area(std::vector< Point >::const_iterator p1, std::vector< Point >::const_iterator p2, double curr)
{
  if (p2 == points.cend())
  {
    return curr;
  }
  curr += calculate_pair(*p1, *p2, curr);
  return calculate_area(++p1, ++p2, curr);
}

double ishmuratov::calculate_pair(const ishmuratov::Point &p1, const ishmuratov::Point &p2, double curr)
{
  return 0.5 * std::abs((p1.x + p2.x) * (p1.y - p2.y));
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