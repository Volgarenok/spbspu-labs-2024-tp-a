#include "commands.hpp"
#include <iostream>
#include <iterator>
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

bool isPointIn(const artemev::Point& point, const artemev::Polygon& shape)
{
  bool isIn = std::find(shape.points.cbegin(), shape.points.cend(), point) != shape.points.cend();
  artemev::Point reversePoint({ point.y, point.x });
  return isIn || std::find(shape.points.cbegin(), shape.points.cend(), reversePoint) != shape.points.cend();
}

bool isPerms(const artemev::Polygon& shape1, const artemev::Polygon& shape2)
{
  if (shape1.points.size() != shape2.points.size())
  {
    return 0;
  }
  using namespace std::placeholders;
  auto perms = std::bind(isPointIn, _1, shape2);
  return std::distance(shape2.points.cbegin(), shape2.points.cend()) == std::count_if(shape1.points.cbegin(), shape1.points.cend(), perms);
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

int accumulateRightAngle(int rightAngles, const artemev::Polygon polygon)
{
  if (polygon.isRightAngle())
  {
    ++rightAngles;
  }

  return rightAngles;
}

void artemev::area(const std::vector< Polygon >& file, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  using namespace std::placeholders;
  if (command == "ODD")
  {
    std::function< double(double, const Polygon&) > accum = std::bind(conditionAccumulatePolygon, _1, _2, isOdd);
    output << std::accumulate(file.cbegin(), file.cend(), 0.0, accum);
  }

  else if (command == "EVEN")
  {
    std::function< double(double, const Polygon&) > accum = std::bind(conditionAccumulatePolygon, _1, _2, isEven);
    output << std::accumulate(file.cbegin(), file.cend(), 0.0, accum);
  }

  else if (command == "MEAN")
  {
    if (file.empty())
    {
      throw std::logic_error("Error! Polygons is empty");
    }
    output << std::accumulate(file.cbegin(), file.cend(), 0.0, accumulatePolygon) / file.size();
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
    output << std::accumulate(file.cbegin(), file.cend(), 0.0, std::bind(countTop, _1, _2, count));
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

void artemev::perms(const std::vector< Polygon >& file, std::istream& input, std::ostream& output)
{
  Polygon shape;
  input >> shape;
  using namespace std::placeholders;
  if (!input || shape.points.empty())
  {
    throw std::invalid_argument("Error! Polygon is strange...");
  }
  auto perms = std::bind(isPerms, _1, shape);
  output << count_if(file.cbegin(), file.cend(), perms);
}

void artemev::rightshapes(const std::vector< Polygon >& file, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  auto accRight = std::bind(accumulateRightAngle, _1, _2);
  output << std::accumulate(file.cbegin(), file.cend(), 0, accRight);
}
