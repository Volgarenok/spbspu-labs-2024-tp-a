#include "polygon.hpp"
#include "delimeter.hpp"

std::istream& feofanova::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tempPoint = {};
  using del = Delimeter_t;
  in >> del{ '(' } >> tempPoint.x >> del{ ';' } >> tempPoint.y >> del{ ')' };
  if (in)
  {
    p = tempPoint;
  }
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& feofanova::operator>>(std::istream& in, Polygon& p)
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
  std::vector<Point> tmp;
  for (size_t i = 0; i < countPoints; i++)
  {
    Point tempPoint = {};
    if (in >> tempPoint)
    {
      tempPoint.push_back(tempPoint);
    }
  }
  if (in)
  {
    p.points = tempPoint;
  }
  return in;
}

std::ostream& feofanova::operator<<(std::ostream& out, const Polygon& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << p.points.size() << ' ';
  using outIt = std::ostream_iterator<Point>;
  std::copy(p.points.cbegin(), p.points.cend(), outIt{ out, " " });
  return out;
}
