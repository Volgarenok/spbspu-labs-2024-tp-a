#include "commands.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include "scope_guard.hpp"
#include "polygon.hpp"
#include "predicates.hpp"

void erohin::doAreaCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  double result = 0.0;
  std::string argument;
  input >> argument;
  std::map< std::string, std::function< double() > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["EVEN"] = std::bind(evaluateAreaEven, context);
    subcommand["ODD"] = std::bind(evaluateAreaOdd, context);
    subcommand["MEAN"] = std::bind(evaluateAreaMean, context);
  }
  try
  {
    size_t number = stoull(argument);
    if (number < 3)
    {
      throw std::logic_error("Cannot be a polygon with such vertex number");
    }
    result = evaluateAreaNum(context, number);
  }
  catch (const std::invalid_argument &)
  {
    result = subcommand[argument]();
  }
  ScopeGuard sg(output);
  output << std::fixed;
  output.precision(1);
  output << result << "\n";
}

double erohin::evaluateAreaNum(const std::vector< Polygon > & context, size_t number)
{
  return getSumAreaIf(context, std::bind(isVertexNumber, std::placeholders::_1, number));
}

double erohin::evaluateAreaEven(const std::vector< Polygon > & context)
{
  return getSumAreaIf(context, isVertexNumberEven);
}

double erohin::evaluateAreaOdd(const std::vector< Polygon > & context)
{
  return getSumAreaIf(context, isVertexNumberOdd);
}

double erohin::evaluateAreaMean(const std::vector< Polygon > & context)
{
  std::vector< double > area;
  std::transform(context.cbegin(), context.cend(), std::back_inserter(area), getArea);
  return std::accumulate(area.cbegin(), area.cend(), 0) / context.size();
}

void erohin::doMaxCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  std::string argument;
  input >> argument;
  std::map< std::string, std::function< void(std::ostream &) > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(findMaxAreaPolygon, context, _1);
    subcommand["VERTEXES"] = std::bind(findMaxVertexesPolygon, context, _1);
  }
  subcommand[argument](output);
}

void erohin::findMaxAreaPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto max_elem = std::max_element(context.cbegin(), context.cend(), isLessByArea);
  ScopeGuard sg(output);
  output << std::fixed;
  output.precision(1);
  output << getArea(*max_elem);
}

void erohin::findMaxVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  output << std::max_element(context.cbegin(), context.cend(), isLessBySize)->points.size();
}

void erohin::doMinCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  std::string argument;
  input >> argument;
  std::map< std::string, std::function< void(std::ostream &) > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(findMinAreaPolygon, context, _1);
    subcommand["VERTEXES"] = std::bind(findMinVertexesPolygon, context, _1);
  }
  subcommand[argument](output);
  output  << "\n";
}

void erohin::findMinAreaPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto max_elem = std::min_element(context.cbegin(), context.cend(), isLessByArea);
  ScopeGuard sg(output);
  output << std::fixed;
  output.precision(1);
  output << getArea(*max_elem);
}

void erohin::findMinVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  output << std::min_element(context.cbegin(), context.cend(), isLessBySize)->points.size();
}

void erohin::doCountCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  std::string argument;
  input >> argument;
  std::map< std::string, std::function< bool(const Polygon &) > > condition;
  condition["EVEN"] = isVertexNumberEven;
  condition["ODD"] = isVertexNumberOdd;
  size_t result = 0;
  try
  {
    size_t number = stoull(argument);
    if (number < 3)
    {
      throw std::logic_error("Cannot be a polygon with such vertex number");
    }
    result = std::count_if(context.cbegin(), context.cend(), std::bind(isVertexNumber, std::placeholders::_1, number));
  }
  catch (const std::invalid_argument &)
  {
    result = std::count_if(context.cbegin(), context.cend(), condition.at(argument));
  }
  output << result << "\n";
}

void erohin::doInFrameCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  Polygon argument;
  input >> argument;
  auto inner_fr = getFrameRect(argument);
  auto outer_fr = getFrameRect(context);
  bool is_left_lower = (outer_fr.first.x <= inner_fr.first.x) && (outer_fr.first.y <= inner_fr.first.y);
  bool is_right_upper = (inner_fr.second.x <= outer_fr.second.x) && (inner_fr.second.y <= outer_fr.second.y);
  output << ((is_left_lower && is_right_upper) ? "<TRUE>" : "<FALSE>") << "\n";
}

void erohin::doRightShapesCommand(const std::vector< Polygon > & context, std::istream &, std::ostream & output)
{
  output << std::count_if(context.cbegin(), context.cend(), hasRightAngles) << "\n";
}
