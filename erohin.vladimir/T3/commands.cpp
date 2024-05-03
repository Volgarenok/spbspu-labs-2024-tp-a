#include "commands.hpp"
#include <vector>
#include <iostream>
#include "polygon.hpp"

void erohin::doInFrame(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  Polygon argument;
  input >> argument;
  output << (isInFrame(context, argument) ? "<TRUE>" : "<FALSE>");
}

void erohin::doRightShapes(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  output << countRightShapes(context);
}

bool erohin::isInFrame(std::vector< Polygon > & context, const Polygon & argument)
{
  return true;
}

size_t erohin::countRightShapes(const std::vector< Polygon > & context)
{
  return 0;
}
