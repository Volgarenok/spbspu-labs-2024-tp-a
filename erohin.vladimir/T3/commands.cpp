#include "commands.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include "polygon.hpp"
#include "predicates.hpp"

void erohin::doInFrame(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  Polygon argument;
  input >> argument;
  output << (isInFrame(context, argument) ? "<TRUE>" : "<FALSE>") << "\n";
}

void erohin::doRightShapes(const std::vector< Polygon > & context, std::istream &, std::ostream & output)
{
  output << countRightShapes(context) << "\n";
}

bool erohin::isInFrame(const std::vector< Polygon > & context, const Polygon & polygon)
{
  int min_x = std::min_element(context.cbegin(), context.cend(), isFrameRectXCoordinateLess)->getFrameRect().first.x;
  int max_x = std::max_element(context.cbegin(), context.cend(), isFrameRectXCoordinateNotGreater)->getFrameRect().second.x;
  int min_y = std::min_element(context.cbegin(), context.cend(), isFrameRectYCoordinateLess)->getFrameRect().first.y;
  int max_y = std::max_element(context.cbegin(), context.cend(), isFrameRectYCoordinateNotGreater)->getFrameRect().second.y;
  std::pair< Point, Point > frameRect = polygon.getFrameRect();
  bool isPointLeftLower = (frameRect.first.x >= min_x) && (frameRect.first.y >= min_y);
  bool isPointRightUpper = (frameRect.second.x <= max_x) && (frameRect.second.y <= max_y);
  return isPointLeftLower && isPointRightUpper;
}

size_t erohin::countRightShapes(const std::vector< Polygon > & context)
{
  return 0;
}
