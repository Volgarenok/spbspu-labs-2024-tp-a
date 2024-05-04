#include "additionalCommands.hpp"

double kuznetsov::getMaxArea(double& maxArea, const Polygon& polygon)
{
  double area = getAreaPolygon(polygon);
  if (area > maxArea)
  {
    maxArea = area;
    return area;
  }
  return maxArea;
}

int kuznetsov::getMaxVertexes(int& maxVertexes, const Polygon& polygon)
{
  int vertexes = polygon.points.size();
  if (vertexes > maxVertexes)
  {
    maxVertexes = vertexes;
    return vertexes;
  }
  return maxVertexes;
}
