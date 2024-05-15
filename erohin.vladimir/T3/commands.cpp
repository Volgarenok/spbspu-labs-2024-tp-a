#include "commands.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
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
    subcommand["EVEN"] = std::bind(countAreaEven, std::ref(context));
    subcommand["ODD"] = std::bind(countAreaOdd, std::ref(context));
    subcommand["MEAN"] = std::bind(countAreaMean, std::ref(context));
  }
  try
  {
    size_t number = stoull(argument);
    result = countAreaNum(context, number);
  }
  catch (const std::invalid_argument &)
  {
    result = subcommand[argument]();
  }
  output << result << "\n";
}

double erohin::countAreaNum(const std::vector< Polygon > & context, size_t number)
{
  std::vector< Polygon > selected;
  std::function< bool(const Polygon &) > compare_func = std::bind(isVertexNumber, std::placeholders::_1, number);
  std::copy_if(context.cbegin(), context.cend(), std::back_inserter(selected), compare_func);
  std::vector< double > area;
  std::transform(context.cbegin(), context.cend(), std::back_inserter(area), getArea);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}

double erohin::countAreaEvev(const std::vector< Polygon > & context, size_t number)
{
  std::vector< Polygon > selected;
  std::function< bool(const Polygon &) > compare_func = std::bind(isVertexNumber, std::placeholders::_1, number);
  std::copy_if(context.cbegin(), context.cend(), std::back_inserter(selected), compare_func);
  std::vector< double > area;
  std::transform(context.cbegin(), context.cend(), std::back_inserter(area), getArea);
  return std::accumulate(area.cbegin(), area.cend(), 0.0);
}

void erohin::doInFrameCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output)
{
  Polygon argument;
  input >> argument;
  output << true << "\n";
}

void erohin::doRightShapesCommand(const std::vector< Polygon > & context, std::istream &, std::ostream & output)
{
  output << 0 << "\n";
}
