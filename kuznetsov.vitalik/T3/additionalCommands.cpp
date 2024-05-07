#include "additionalCommands.hpp"
#include <utility>

double kuznetsov::getMaxOrMinArea(bool cur, double& maxOrMinArea, const Polygon& polygon)
{
  double area = getAreaPolygon(polygon);
  if (cur)
  {
    if (area > maxOrMinArea)
    {
      maxOrMinArea = area;
      return area;
    }
  }
  else
  {
    if (area < maxOrMinArea)
    {
      maxOrMinArea = area;
      return area;
    }
  }
  return maxOrMinArea;
}

size_t kuznetsov::getMaxOrMinVertexes(bool cur, size_t& maxOrMinVertexes, const Polygon& polygon)
{
  size_t vertexes = polygon.points.size();
  if (cur)
  {
    if (vertexes > maxOrMinVertexes)
    {
        maxOrMinVertexes = vertexes;
        return vertexes;
    }
  }
  else
  {
    if (vertexes < maxOrMinVertexes)
    {
      maxOrMinVertexes = vertexes;
      return vertexes;
    }
  }
  return maxOrMinVertexes;
}

int kuznetsov::getCountOfOddOrEvenVertexes(bool cur, int sum, const Polygon& polygon)
{
  if (!cur && polygon.points.size() % 2 == 1)
  {
    return sum + 1;
  }
  else if (cur && polygon.points.size() % 2 == 0)
  {
    return sum + 1;
  }
  else
  {
    return sum;
  }
}

int kuznetsov::getCountWithNumVertexes(size_t num, int sum, const Polygon& polygon)
{
  if (num == polygon.points.size())
  {
    return sum + 1;
  }
  return sum;
}

