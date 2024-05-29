#include "predicates.hpp"
#include <algorithm>
#include <functional>

bool kuznetsov::isEvenVertexes(const Polygon& shape)
{
  return shape.points.size() % 2 == 0;
}

bool kuznetsov::isOddVertexes(const Polygon& shape)
{
  return shape.points.size() % 2 == 1;
}

bool kuznetsov::isNumEqualSize(const Polygon& shape, size_t num)
{
  return num == shape.points.size();
}

bool kuznetsov::isMax()
{
  return true;
}

bool kuznetsov::isMin()
{
  return false;
}
