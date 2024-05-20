#include "commands.hpp"
#include <iostream>
#include <iterator>
#include <iomanip>
#include <functional>
#include <numeric>
#include <algorithm>
#include "shapes.hpp"

bool isOdd(const artemev::Polygon& shape)
{
  return shape.points.size() % 2;
}

bool isEven(const artemev::Polygon& shape)
{
  return !(shape.points.size() % 2);
}

bool isSize(const artemev::Polygon& figure, size_t ptsNum)
{
  return figure.points.size() == ptsNum;
}

bool isCorrectCountAngle(const artemev::Polygon& shape, size_t countTop)
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

bool comparatorA(const artemev::Polygon& rhs, const artemev::Polygon& lhs)
{
  return getArea(rhs) < getArea(lhs);
}

bool comparatorT(const artemev::Polygon& rhs, const artemev::Polygon& lhs)
{
  return rhs.points.size() < lhs.points.size();
}

bool isRight(const artemev::Polygon& polygon)
{
  return countRightAngle(polygon);
}

void artemev::area(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  std::vector< Polygon > pol;
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  using namespace std::placeholders;
  if (command == "ODD")
  {
    std::copy_if(figure.cbegin(), figure.cend(), std::back_inserter(pol), isOdd);
  }

  else if (command == "EVEN")
  {
    std::copy_if(figure.cbegin(), figure.cend(), std::back_inserter(pol), isEven);
  }

  else if (command == "MEAN")
  {
    if (figure.empty())
    {
      throw std::logic_error("Error! Polygons is empty");
    }
    std::copy(figure.cbegin(), figure.cend(), std::back_inserter(pol));
  }

  else
  {
    size_t count;
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
    std::function< bool(const Polygon&) > pred = std::bind(isSize, _1, count);
    std::copy_if(figure.cbegin(), figure.cend(), std::back_inserter(pol), pred);
  }

  std::vector< double > areas;
  std::transform(pol.cbegin(), pol.cend(), std::back_inserter(areas), getArea);
  double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (command == "MEAN")
  {
    res /= figure.size();
  }
  output << res; 
}

void artemev::max(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  if (figure.empty())
  {
    throw std::logic_error("Error! Polygon is empty");
  }

  if (command == "AREA")
  {
    output << getArea(*std::max_element(figure.cbegin(), figure.cend(), comparatorA));
  }

  else if (command == "VERTEXES")
  {
    output << (*std::max_element(figure.cbegin(), figure.cend(), comparatorT)).points.size();
  }

  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void artemev::min(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  if (figure.empty())
  {
    throw std::logic_error("Error! Polygon is empty");
  }

  if (command == "AREA")
  {
    output << getArea(*std::min_element(figure.cbegin(), figure.cend(), comparatorA));
  }

  else if (command == "VERTEXES")
  {
    output << (*std::min_element(figure.cbegin(), figure.cend(), comparatorT)).points.size();
  }

  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void artemev::count(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string command;
  input >> command;

  using namespace std::placeholders;
  if (command == "EVEN")
  {
    output << std::count_if(figure.cbegin(), figure.cend(), isEven);
  }

  else if (command == "ODD")
  {
    output << std::count_if(figure.cbegin(), figure.cend(), isOdd);
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
    output << std::count_if(figure.cbegin(), figure.cend(), countPred);
  }
}

void artemev::perms(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  Polygon shape;
  input >> shape;
  using namespace std::placeholders;
  if (!input || shape.points.empty())
  {
    throw std::invalid_argument("Error! Polygon is strange...");
  }
  auto perms = std::bind(isPerms, _1, shape);
  output << count_if(figure.cbegin(), figure.cend(), perms);
}

void artemev::rightShapes(const std::vector< Polygon >& figure, std::ostream& output)
{
  output << std::count_if(figure.cbegin(), figure.cend(), isRight);
}
