#include "predicates.hpp"
#include <algorithm>
#include <functional>

bool kuznetsov::isEvenVertexes(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool kuznetsov::isOddVertexes(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}

bool kuznetsov::isNumEqualSize(const Polygon& polygon, size_t num)
{
  return num == polygon.points.size();
}

bool kuznetsov::isMax()
{
  return true;
}

bool kuznetsov::isMin()
{
  return false;
}
