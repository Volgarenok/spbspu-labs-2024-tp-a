#include "commands.hpp"
#include <istream>
#include <vector>
#include <string>
#include <numeric>
#include <functional>
#include <algorithm>
#include "figures_struct.hpp"

double accumulatePolygon(double result, const nikitov::Polygon& figure)
{
  result += figure.getArea();
  return result;
}

double accumulatePolygonIf(double result, const nikitov::Polygon& figure, bool(*predicate)(const nikitov::Polygon&))
{
  if (predicate(figure))
  {
    result += figure.getArea();
  }
  return result;
}

bool isSize(const nikitov::Polygon& figure, size_t pointsNum)
{
  return figure.points.size() == pointsNum;
}

bool isOdd(const nikitov::Polygon& figure)
{
  return figure.points.size() % 2;
}

bool isEven(const nikitov::Polygon& figure)
{
  return !(figure.points.size() % 2);
}

void nikitov::area(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  std::string parameter = {};
  input >> parameter;
  using namespace std::placeholders;
  if (parameter == "ODD")
  {
    std::function< double(double, const Polygon&) > accum = std::bind(accumulatePolygonIf, _1, _2, isOdd);
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accum);
  }
  else if (parameter == "EVEN")
  {
    std::function< double(double, const Polygon&) > accum = std::bind(accumulatePolygonIf, _1, _2, isEven);
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accum);
  }
  else if (parameter == "MEAN")
  {
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accumulatePolygon) / data.size();
  }
  else if (std::all_of(parameter.cbegin(), parameter.cend(), ::isdigit))
  {
    
  }
  else
  {
    output << "<INVALID COMMAND>";
  }
}

void nikitov::max(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  std::string parameter = {};
  input >> parameter;

  if (parameter == "AREA")
  {

  }
  else if (parameter == "VERTEXES")
  {

  }
  else
  {
    output << "<INVALID COMMAND>";
  }
}

void nikitov::min(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  std::string parameter = {};
  input >> parameter;

  if (parameter == "AREA")
  {

  }
  else if (parameter == "VERTEXES")
  {

  }
  else
  {
    output << "<INVALID COMMAND>";
  }
}

void nikitov::count(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  std::string parameter = {};
  input >> parameter;

  if (parameter == "EVEN")
  {
    output << std::count_if(data.cbegin(), data.cend(), isEven);
  }
  else if (parameter == "ODD")
  {
    output << std::count_if(data.cbegin(), data.cend(), isOdd);
  }
  else if (std::all_of(parameter.cbegin(), parameter.cend(), ::isdigit))
  {

  }
  else
  {
    output << "<INVALID COMMAND>";
  }
}
