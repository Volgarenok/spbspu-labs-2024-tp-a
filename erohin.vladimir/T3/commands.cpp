#include "commands.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include "scope_guard.hpp"
#include "polygon.hpp"

void erohin::doAreaCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  double result = 0.0;
  std::string argument;
  input >> argument;
  std::map< std::string, std::function< double() > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["EVEN"] = std::bind(detail::evaluateAreaEven, context);
    subcommand["ODD"] = std::bind(detail::evaluateAreaOdd, context);
    subcommand["MEAN"] = std::bind(detail::evaluateAreaMean, context);
  }
  try
  {
    size_t number = std::stoull(argument);
    if (number < 3)
    {
      throw std::logic_error("Cannot be a polygon with such vertex number");
    }
    result = detail::evaluateAreaNum(context, number);
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

void erohin::doMaxCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  std::string argument;
  input >> argument;
  std::map< std::string, std::function< void(std::ostream &) > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(detail::findMaxAreaPolygon, context, _1);
    subcommand["VERTEXES"] = std::bind(detail::findMaxVertexesPolygon, context, _1);
  }
  subcommand[argument](output);
}

void erohin::doMinCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  std::string argument;
  input >> argument;
  std::map< std::string, std::function< void(std::ostream &) > > subcommand;
  {
    using namespace std::placeholders;
    subcommand["AREA"] = std::bind(detail::findMinAreaPolygon, context, _1);
    subcommand["VERTEXES"] = std::bind(detail::findMinVertexesPolygon, context, _1);
  }
  subcommand[argument](output);
  output  << "\n";
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
    size_t number = std::stoull(argument);
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
  if (!(input && input.peek() == '\n'))
  {
    throw std::invalid_argument("Wrong polygon input");
  }
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

double erohin::detail::evaluateAreaNum(const std::vector< Polygon > & context, size_t number)
{
  return getSumAreaIf(context, std::bind(isVertexNumber, std::placeholders::_1, number));
}

double erohin::detail::evaluateAreaEven(const std::vector< Polygon > & context)
{
  return getSumAreaIf(context, isVertexNumberEven);
}

double erohin::detail::evaluateAreaOdd(const std::vector< Polygon > & context)
{
  return getSumAreaIf(context, isVertexNumberOdd);
}

double erohin::detail::evaluateAreaMean(const std::vector< Polygon > & context)
{
  if (context.empty())
  {
    throw std::logic_error("Cannot count mean polygon area");
  }
  return (getArea(context) / context.size());
}

void erohin::detail::findMaxAreaPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto max_elem = std::max_element(context.cbegin(), context.cend(), isLessByArea);
  if (max_elem == context.cend())
  {
    throw std::logic_error("Cannot find max value in empty context");
  }
  ScopeGuard sg(output);
  output << std::fixed;
  output.precision(1);
  output << getArea(*max_elem) << "\n";
}

void erohin::detail::findMaxVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto max_elem = std::max_element(context.cbegin(), context.cend(), isLessBySize);
  if (max_elem == context.cend())
  {
    throw std::logic_error("Cannot find max value in empty context");
  }
  output << max_elem->points.size() << "\n";
}

void erohin::detail::findMinAreaPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto min_elem = std::min_element(context.cbegin(), context.cend(), isLessByArea);
  if (min_elem == context.cend())
  {
    throw std::logic_error("Cannot find max value in empty context");
  }
  ScopeGuard sg(output);
  output << std::fixed;
  output.precision(1);
  output << getArea(*min_elem) << "\n";
}

void erohin::detail::findMinVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto min_elem = std::min_element(context.cbegin(), context.cend(), isLessBySize);
  if (min_elem == context.cend())
  {
    throw std::logic_error("Cannot find max value in empty context");
  }
  output << min_elem->points.size() << "\n";
}
