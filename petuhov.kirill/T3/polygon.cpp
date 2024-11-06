#include "polygon.hpp"
#include <sstream>

bool petuhov::operator==(const Polygon &a, const Polygon &b)
{
  return a.points == b.points;
}

std::istream &petuhov::operator>>(std::istream &is, petuhov::Polygon &polygon)
{
  int num_points;
  if (is >> num_points)
  {
    polygon.points.clear();
    for (int i = 0; i < num_points; ++i)
    {
      char ch1, ch2, ch3;
      petuhov::Point point;
      if (is >> ch1 >> point.x_ >> ch2 >> point.y_ >> ch3 && ch1 == '(' && ch2 == ';' && ch3 == ')')
      {
        polygon.points.push_back(point);
      }
      else
      {
        is.setstate(std::ios::failbit);
        break;
      }
    }
    if (polygon.points.size() != static_cast<size_t>(num_points))
    {
      is.setstate(std::ios::failbit);
    }
  }
  return is;
}
