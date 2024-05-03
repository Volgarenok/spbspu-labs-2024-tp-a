#include "polygon.hpp"
#include <iostream>
#include <iterator>
#include <algorithm>
#include "delimiter.hpp"

int erohin::Point::getX() const
{
  return x;
}

int erohin::Point::getY() const
{
  return y;
}

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

std::pair< Point, Point > erohin::Polygon::getFrameRect() const
{
  std::pair< Point, Point > res;
  std::vector< int > coord;
  std::transform(points.cbegin(), points.cend(), coord.begin(), Point::getX);
  int min_x = *std::min_element(coord.cbegin, coord.cend());
  int max_x = *std::max_element(coord.cbegin(), coord.cend());
  coord.clear();
  std::transform(points.cbegin(), points.cend(), coord.begin(), Point::getY);
  int min_y = *std::min_element(coord.cbegin, coord.cend());
  int max_y = *std::max_element(coord.cbegin(), coord.cend());
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
