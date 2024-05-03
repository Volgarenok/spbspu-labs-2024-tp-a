#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include "delimiter.hpp"
#include "binary_predicates.hpp"

std::istream & erohin::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  Point temp;
  input >> Delimiter{'('} >> point.x >> Delimiter{';'} >> point.y >> Delimiter{')'};
  if (!input)
  {
    point = temp;
  }
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const Point & point)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << '(' << point.x << ';' << point.y << ')';
  return output;
}

std::pair< erohin::Point, erohin::Point > erohin::Polygon::getFrameRect() const
{
  std::pair< Point, Point > res;
  int min_x = std::min_element(points.cbegin(), points.cend(), isXCoordinateLess)->x;
  int max_x = std::max_element(points.cbegin(), points.cend(), isXCoordinateLess)->x;
  int min_y = std::min_element(points.cbegin(), points.cend(), isYCoordinateLess)->y;
  int max_y = std::max_element(points.cbegin(), points.cend(), isYCoordinateLess)->y;
  return std::make_pair(Point{ min_x, min_y }, Point{ max_x, max_y });
}

std::istream & erohin::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  size_t count = 0;
  input >> count;
  if (count < 3)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  std::vector< Point > temp;
  temp.reserve(count);
  std::copy_n(
    std::istream_iterator< Point >(input),
    count,
    std::back_inserter(temp)
  );
  if (input)
  {
    polygon.points = std::move(temp);
  }
  return input;
}

std::ostream & erohin::operator<<(std::ostream & output, const Polygon & polygon)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  output << polygon.points.size() << " ";
  std::copy(
    polygon.points.cbegin(),
    polygon.points.cend(),
    std::ostream_iterator< Point >(output, " ")
  );
  return output;
}
