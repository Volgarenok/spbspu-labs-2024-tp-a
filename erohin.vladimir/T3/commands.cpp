#include "commands.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include "scope_guard.hpp"
#include "polygon.hpp"

namespace erohin
{
  double evaluateAreaNum(const std::vector< Polygon > & context, size_t number);
  double evaluateAreaEven(const std::vector< Polygon > & context);
  double evaluateAreaOdd(const std::vector< Polygon > & context);
  double evaluateAreaMean(const std::vector< Polygon > & context);
}

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
    size_t number = std::stoull(argument);
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

namespace erohin
{
  void findMaxAreaPolygon(const std::vector< Polygon > & context, std::ostream & output);
  void findMaxVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output);
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

namespace erohin
{
  void findMinAreaPolygon(const std::vector< Polygon > & context, std::ostream & output);
  void findMinVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output);
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
}

namespace erohin
{
  bool isVertexNumberEven(const Polygon & polygon);
  bool isVertexNumberOdd(const Polygon & polygon);
  bool isVertexNumber(const Polygon & polygon, size_t number);
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

double erohin::evaluateAreaNum(const std::vector< Polygon > & context, size_t number)
{
  return detail::getSumAreaIf(context, std::bind(isVertexNumber, std::placeholders::_1, number));
}

double erohin::evaluateAreaEven(const std::vector< Polygon > & context)
{
  return detail::getSumAreaIf(context, isVertexNumberEven);
}

double erohin::evaluateAreaOdd(const std::vector< Polygon > & context)
{
  return detail::getSumAreaIf(context, isVertexNumberOdd);
}

double erohin::evaluateAreaMean(const std::vector< Polygon > & context)
{
  if (context.empty())
  {
    throw std::logic_error("Cannot count mean polygon area");
  }
  return (getArea(context) / context.size());
}

namespace erohin
{
  bool isLessByArea(const Polygon & lhs, const Polygon & rhs);
  bool isLessBySize(const Polygon & lhs, const Polygon & rhs);
}

void erohin::findMaxAreaPolygon(const std::vector< Polygon > & context, std::ostream & output)
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

void erohin::findMaxVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto max_elem = std::max_element(context.cbegin(), context.cend(), isLessBySize);
  if (max_elem == context.cend())
  {
    throw std::logic_error("Cannot find max value in empty context");
  }
  output << max_elem->points.size() << "\n";
}

void erohin::findMinAreaPolygon(const std::vector< Polygon > & context, std::ostream & output)
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

void erohin::findMinVertexesPolygon(const std::vector< Polygon > & context, std::ostream & output)
{
  auto min_elem = std::min_element(context.cbegin(), context.cend(), isLessBySize);
  if (min_elem == context.cend())
  {
    throw std::logic_error("Cannot find max value in empty context");
  }
  output << min_elem->points.size() << "\n";
}

bool erohin::isVertexNumberEven(const Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool erohin::isVertexNumberOdd(const Polygon & polygon)
{
  return !isVertexNumberEven(polygon);
}

bool erohin::isVertexNumber(const Polygon & polygon, size_t number)
{
  return (polygon.points.size() == number);
}

bool erohin::isLessByArea(const Polygon & lhs, const Polygon & rhs)
{
  return (getArea(lhs) < getArea(rhs));
}

bool erohin::isLessBySize(const Polygon & lhs, const Polygon & rhs)
{
  return (lhs.points.size() < rhs.points.size());
}
