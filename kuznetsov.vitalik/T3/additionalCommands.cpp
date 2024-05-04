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
