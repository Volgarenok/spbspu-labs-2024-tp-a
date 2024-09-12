#include "polygon.hpp"

std::istream & sakovskaia::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  using delimiter = Delimiter;
  Point data{0, 0};
  input >> delimiter{"("} >> data.x >> delimiter{";"} >> data.y >> delimiter{")"};
  if (input)
  {
    point = data;
  }
  return input;
}

std::istream & sakovskaia::operator>>(std::istream & input, Polygon & polygon)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  size_t cnt = 0;
  input >> cnt;
  if (cnt < 3)
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  std::vector< Point > data;
  using input_it = std::istream_iterator< Point >;
  std::copy_n(input_it{ input }, cnt, std::back_inserter(data));
  if (input && data.size() == cnt)
  {
    polygon.points = data;
  }
  return input;
}

size_t sakovskaia::get_size(const Polygon & polygon)
{
  return polygon.points.size();
}

int sakovskaia::get_x(const Point & p)
{
  return p.x;
}

int sakovskaia::get_y(const Point & p)
{
  return p.y;
}

bool sakovskaia::operator==(const Polygon & lhs, const Polygon & rhs)
{
  return lhs.points == rhs.points;
}

bool sakovskaia::operator==(const Point & lhs, const Point & rhs)
{
  return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}
