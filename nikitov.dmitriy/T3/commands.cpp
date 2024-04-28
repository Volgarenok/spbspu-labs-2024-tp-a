#include "commands.hpp"
#include <istream>
#include <vector>
#include <string>
#include <numeric>
#include <functional>
#include "figures_struct.hpp"

double accumulatePolygon(double result, const nikitov::Polygon& figure, bool(*predicat)(const nikitov::Polygon&))
{
  if (predicat(figure))
  {
    result += figure.getArea();
  }
  return result;
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
    std::function< double(double, const Polygon&) > accum = std::bind(accumulatePolygon, _1, _2, isOdd);
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accum);
  }
  else if (parameter == "EVEN")
  {
    std::function< double(double, const Polygon&) > accum = std::bind(accumulatePolygon, _1, _2, isEven);
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accum);
  }
}
