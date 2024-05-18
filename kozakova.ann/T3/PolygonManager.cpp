#include "PolygonManager.hpp"

double kozakova::PolygonArea::operator()(const Point& second)
{
  double area = (second.x + first.x) * (first.y - second.y);
  first = second;
  return area;
}

bool kozakova::PolygonMaxSeq::operator()(const Polygon& polygon, const Polygon& data)
{
  if (polygon == data)
  {
    cur++;
    maxseq = std::max(maxseq, cur);
  }
  else
  {
    cur = 0;
  }
  return maxseq;
}
