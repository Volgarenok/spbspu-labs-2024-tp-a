#include "commands.hpp"
#include <istream>
#include <iomanip>
#include <functional>
#include <numeric>

bool isOdd(const artemev::Polygon& shape)
{
  return shape.points.size() % 2;
}

bool isEven(const artemev::Polygon& shape)
{
  return !(shape.points.size() % 2);
}

double conditionAccumulatePolygon(double result, const artemev::Polygon& figure, std::function< bool(const artemev::Polygon&) > predicate)
{
  if (predicate(figure))
  {
    result += figure.getArea();
  }
  return result;
}

void artemev::area(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  using namespace std::placeholders;
  if (command == "ODD")
  {
    std::function< double(double, const Polygon&) > accum = std::bind(conditionAccumulatePolygon, _1, _2, isOdd);
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accum);
  }
  
  else if (command == "EVEN")
  {
    std::function< double(double, const Polygon&) > accum = std::bind(conditionAccumulatePolygon, _1, _2, isEven);
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accum);
  }
}