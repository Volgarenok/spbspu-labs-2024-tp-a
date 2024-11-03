#include "polygon.hpp"


std::istream & kovtun::operator>>(std::istream & in, kovtun::Polygon & polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using dl = kovtun::DelimiterI;

  polygon.points.clear();
  size_t size = 0;
  in >> size;
  for (size_t i = 0; i < size; ++i)
  {
    kovtun::Point point = {};
    in >> dl{'('} >> point.x >> dl{';'} >> point.y >> dl{')'};
    polygon.points.push_back(point);
  }

  return in;
}

double kovtun::getArea(kovtun::Polygon & polygon)
{
  size_t size = polygon.points.size();
  auto pts = polygon.points;

  int firstSum = 0;
  for (int i = 0; i < size - 1; i++)
  {
    firstSum += pts[i].x * pts[i+1].y;
  }
  firstSum += pts[size-1].x * pts[0].y;

  int secondSum = 0;
  for (int i = 0; i < size - 1; i++)
  {
    secondSum += pts[i+1].x * pts[i].y;
  }
  secondSum += pts[0].x * pts[size-1].y;

  double result = std::abs(firstSum - secondSum) * 0.5;
  return result;
}
