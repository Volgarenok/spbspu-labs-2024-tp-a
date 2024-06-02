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

bool isPerms(const artemev::Polygon& shape1, const artemev::Polygon& shape2)
{
  if (shape1.points.size() != shape2.points.size())
  {
    return 0;
  }
  return std::is_permutation(shape1.points.cbegin(), shape1.points.cend(), shape2.points.cbegin());
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

void artemev::getAreaCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  std::vector< Polygon > pol;
  pol.reserve(figure.size());
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
    catch (const std::invalid_argument&)
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

  std::vector< double > areas(pol.size());
  std::transform(pol.cbegin(), pol.cend(), std::back_inserter(areas), getArea);
  double res = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (command == "MEAN")
  {
    res /= figure.size();
  }
  output << res;
}

void minOrMax(const std::vector< artemev::Polygon >& figure, std::istream& input, std::ostream& output, const std::string& pred)
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
    if (pred == "MIN")
    {
      output << getArea(*std::min_element(figure.cbegin(), figure.cend(), comparatorA));
    }
    else
    {
      output << getArea(*std::max_element(figure.cbegin(), figure.cend(), comparatorA));
    }
  }

  else if (command == "VERTEXES")
  {
    if (pred == "MIN")
    {
      output << (*std::min_element(figure.cbegin(), figure.cend(), comparatorT)).points.size();
    }
    else
    {
      output << (*std::max_element(figure.cbegin(), figure.cend(), comparatorT)).points.size();
    }
  }

  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void artemev::getMaxCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  minOrMax(figure, input, output, "MAX");
}

void artemev::getMinCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
{
  minOrMax(figure, input, output, "MIN");
}

void artemev::getCountCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
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
    size_t count = 0;
    const size_t minCountTop = 3;
    try
    {
      count = std::stoul(command);
    }
    catch (const std::invalid_argument&)
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

void artemev::getPermsCmd(const std::vector< Polygon >& figure, std::istream& input, std::ostream& output)
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

void artemev::getRightShapesCmd(const std::vector< Polygon >& figure, std::ostream& output)
{
  output << std::count_if(figure.cbegin(), figure.cend(), isRight);
}
