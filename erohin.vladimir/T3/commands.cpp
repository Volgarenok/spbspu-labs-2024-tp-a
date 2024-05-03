#include "commands.hpp"
#include <vector>
#include <iostream>
#include "polygon.hpp"

void erohin::isInFrame(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  Polygon argument;
  input >> argument;
  output << (detail::isInFrameImpl(context, argument) ? "<TRUE>" : "<FALSE>");
}

void erohin::countRightShapes(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  output << detail::countRightShapesImpl(context);
}

bool erohin::detail::isInFrameImpl(std::vector< Polygon > & context, const Polygon & argument)
{
  return true;
}

size_t erohin::detail::countRightShapesImpl(const std::vector< Polygon > & context)
{
  return 0;
}
