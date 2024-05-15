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

bool erohin::isInFrame(const std::vector< Polygon > &, const Polygon &)
{
  return true;
}

size_t erohin::countRightShapes(const std::vector< Polygon > & context)
{
  context.end();
  return 0;
}
