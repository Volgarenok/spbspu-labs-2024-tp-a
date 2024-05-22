#include "commands.hpp"
#include <string>
#include <map>
#include <iostream>
#include <numeric>
#include <iterator>
#include <functional>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include "additionalCommands.hpp"

void kuznetsov::getArea(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  double area = 0.0;
  std::string argument;
  in >> argument;
  std::map< std::string, std::function< double() > > cmd;
  {
    using namespace std::placeholders;
    cmd["EVEN"] = std::bind(getOddEvenMean, polygon, Even);
    cmd["ODD"] = std::bind(getOddEvenMean, polygon, Odd);
    cmd["MEAN"] = std::bind(getOddEvenMean, polygon, Mean);
  }
  try
  {
    if (!std::all_of(argument.cbegin(), argument.cend(), std::isdigit))
    {
      throw std::invalid_argument("Wrong argument");
    }
    size_t num = std::stoi(argument);
    if (num < 3)
    {
      throw std::invalid_argument("Wrong number vertexes");
    }
    std::vector< Polygon > sortShape;
    auto operation = std::bind(isNumEqualSize, std::placeholders::_1, num);
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(sortShape), operation);
    std::vector< double > areasShape;
    std::transform(sortShape.cbegin(), sortShape.cend(), std::back_inserter(areasShape), countAreaShape);
    area = std::accumulate(areasShape.cbegin(), areasShape.cend(), 0.0);
  }
  catch (const std::invalid_argument&)
  {
    area = cmd[argument]();
  }
  out << std::fixed << std::setprecision(1) << area << '\n';
}

void kuznetsov::getMax(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string argument;
  in >> argument;
  std::map< std::string, std::function< void(std::ostream&) > > cmd;
  {
    using namespace std::placeholders;
    cmd["AREA"] = std::bind(getMinOrMaxArea, _1, polygon, Max);
    cmd["VERTEXES"] = std::bind(getMinOrMaxVertexes, _1, polygon, Max);
  }
  cmd[argument](out);
}

void kuznetsov::getMin(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string argument;
  in >> argument;
  std::map< std::string, std::function<  void(std::ostream&) > > cmd;
  {
    using namespace std::placeholders;
    cmd["AREA"] = std::bind(getMinOrMaxArea, _1, polygon, Min);
    cmd["VERTEXES"] = std::bind(getMinOrMaxVertexes, _1, polygon, Min);
  }
  cmd[argument](out);
}

void kuznetsov::getCount(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  int count = 0;
  std::string argument;
  in >> argument;
  std::map< std::string, std::function< size_t() > > cmd;
  {
    using namespace std::placeholders;
    cmd["EVEN"] = std::bind(countShapesWithEvenOrOddVertexes, polygon, Even);
    cmd["ODD"] = std::bind(countShapesWithEvenOrOddVertexes, polygon, Odd);
  }
  try
  {
    if (!std::all_of(argument.cbegin(), argument.cend(), ::isdigit))
    {
      throw std::invalid_argument("Wrong argument");
    }
    size_t num = std::stoi(argument);
    if (num < 3)
    {
      throw std::invalid_argument("Wrong number vertexes");
    }
    auto operation = std::bind(isNumEqualSize, std::placeholders::_1, num);
    count = count_if(polygon.begin(), polygon.end(), operation);
  }
  catch (const std::invalid_argument&)
  {
    count = cmd[argument]();
  }
  out << count << '\n';
}

void kuznetsov::getSame(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  Polygon shape;
  in >> shape;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("Invalid argument for polygon");
  }
  using namespace std::placeholders;
  auto countSame = std::bind(areSame, _1, shape);
  out << std::count_if(polygon.cbegin(), polygon.cend(), countSame) << '\n';
}

void kuznetsov::getInframe(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  Polygon shape;
  in >> shape;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("Invalid argument for polygon");
  }

  std::pair< Point, Point> frameRectangle = getFrameRectangle(polygon);

  if (ifInFrameRectangle(shape, frameRectangle))
  {
    out << "<TRUE>\n";
  }
  else
  {
    out << "<FALSE>\n";
  }
}
