#include "commands.hpp"
#include <istream>
#include <iomanip>
#include <functional>
#include <numeric>
#include "shapes.hpp"

bool isOdd(const artemev::Polygon& shape)
{
  return shape.points.size() % 2;
}

bool isEven(const artemev::Polygon& shape)
{
  return !(shape.points.size() % 2);
}

bool isCorrectCountAngle(const artemev::Polygon& shape, int countTop)
{
  return countTop == shape.points.size();
}

double accumulatePolygon(double result, const artemev::Polygon& figure)
{
  result += figure.getArea();
  return result;
}

double conditionAccumulatePolygon(double result, const artemev::Polygon& figure, std::function< bool(const artemev::Polygon&) > predicate)
{
  if (predicate(figure))
  {
    result += figure.getArea();
  }
  return result;
}

double countTop(double result, const artemev::Polygon& figure, int count)
{
  if (figure.points.size() == count)
  {
    result += figure.getArea();
  }
  return result;
}

bool comparatorA(const artemev::Polygon& rhs, const artemev::Polygon& lhs)
{
  return rhs.getArea() < lhs.getArea();
}

bool comparatorT(const artemev::Polygon& rhs, const artemev::Polygon& lhs)
{
  return rhs.points.size() < lhs.points.size();
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

  else if (command == "MEAN")
  {
    if (data.empty())
    {
      throw std::logic_error("Error! Polygons is empty");
    }
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, accumulatePolygon) / data.size();
  }

  else
  {
    int count;
    const int minCountTop = 3;
    try
    {
      count = std::stoul(command);
    }
    catch(const std::invalid_argument&)
    {
      throw std::logic_error("<Error!>");
    }
    if (count < minCountTop)
    {
      throw std::logic_error("<Error! Wrong number of top>");
    }
    output << std::accumulate(data.cbegin(), data.cend(), 0.0, std::bind(countTop, _1, _2, count));
  }
}

void artemev::max(const std::vector< Polygon >& file, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  if (file.empty())
  {
    throw std::logic_error("Error! Polygon is empty");
  }

  if (command == "AREA")
  {
    output << (*std::max_element(file.cbegin(), file.cend(), comparatorA)).getArea();
  }

  else if (command == "VERTEXES")
  {
    output << (*std::max_element(file.cbegin(), file.cend(), comparatorT)).points.size();
  }

  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void artemev::min(const std::vector< Polygon >& file, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  if (file.empty())
  {
    throw std::logic_error("Error! Polygon is empty");
  }

  if (command == "AREA")
  {
    output << (*std::min_element(file.cbegin(), file.cend(), comparatorA)).getArea();
  }

  else if (command == "VERTEXES")
  {
    output << (*std::min_element(file.cbegin(), file.cend(), comparatorT)).points.size();
  }

  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void artemev::count(const std::vector< Polygon >& file, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  using namespace std::placeholders;
  if (command == "EVEN")
  {
    output << std::count_if(file.cbegin(), file.cend(), isEven);
  }

  else if (command == "ODD")
  {
    output << std::count_if(file.cbegin(), file.cend(), isOdd);
  }

  else
  {
    int count;
    const int minCountTop = 3;
    try
    {
      count = std::stoul(command);
    }
    catch(const std::invalid_argument&)
    {
      throw std::logic_error("<Error!>");
    }
    if (count < minCountTop)
    {
      throw std::logic_error("<Error! Wrong number of top>");
    }
    std::function< bool(const Polygon&) > countPred;
    countPred = std::bind(isCorrectCountAngle, _1, count);
    output << std::count_if(file.cbegin(), file.cend(), countPred);
  }
}