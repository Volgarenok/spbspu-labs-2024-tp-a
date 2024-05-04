#include "additionalCommands.hpp"

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

int kuznetsov::getMaxOrMinVertexes(bool cur, int& maxOrMinVertexes, const Polygon& polygon)
{
  int vertexes = polygon.points.size();
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

int kuznetsov::getCountWithNumVertexes(int num, int sum, const Polygon& polygon)
{
  if (num == polygon.points.size())
  {
    return sum + 1;
  }
  return sum;
}
