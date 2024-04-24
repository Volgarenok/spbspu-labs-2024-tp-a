#include "polygon.hpp"
#include <iterator>
#include "delimiter.hpp"

std::istream& novokhatskiy::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp = {};
  in >> strictDel{ '(' } >> tmp.x >> strictDel{ ';' } >> tmp.y >> strictDel{ ')' };
  if (in)
  {
    p = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& novokhatskiy::operator>>(std::istream& in, Polygon& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  size_t countPoints = {};
  in >> countPoints;
  if (countPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > tmp;
  for (size_t i = 0; i < countPoints; i++)
  {
    Point tmpP = {};
    if (in >> tmpP)
    {
      tmp.push_back(tmpP);
    }
  }
  if (in)
  {
    p.points = tmp;
  }
  return in;
}

std::ostream& novokhatskiy::operator<<(std::ostream& out, const Polygon& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using outIt = std::ostream_iterator< Point >;
  out << p.points.size() << ' ';
  std::copy(p.points.cbegin(), p.points.cend(), outIt{ out, " " });
  return out;
}
