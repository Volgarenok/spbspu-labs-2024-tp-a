#include "commands.hpp"
#include <string>
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
  std::string cmd;
  in >> cmd;
  if (cmd == "EVEN")
  {
    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaEvenOrOdd, true, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  else if (cmd == "ODD")
  {
    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaEvenOrOdd, false, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  else if (cmd == "MEAN")
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("The polygon must contain at least one shape.\n");
    }
    double area = 0.0;
    using namespace std::placeholders;
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, getAreaPolygonForMean);
    out << std::fixed << std::setprecision(1) << area / polygon.size() << '\n';
  }
  else if (std::all_of(cmd.cbegin(), cmd.cend(), ::isdigit))
  {
    size_t num = std::stoi(cmd);

    if (num < 3)
    {
      throw std::invalid_argument("The entered number of vertices must be greater than 3.");
    }

    double area = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getAreaPolygonForNum, num, _1, _2);
    area += std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void kuznetsov::getMax(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  if (polygon.empty())
  {
    throw std::invalid_argument("Polygon empty\n");
    return;
  }
  std::string cmd;
  in >> cmd;
  if (cmd == "AREA")
  {
    double maxArea = 0.0;
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinArea, true, maxArea, _2);
    maxArea = std::accumulate(polygon.cbegin(), polygon.cend(), 0.0, operation);
    out << std::fixed << std::setprecision(1) << maxArea << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    size_t maxVertexes = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinVertexes, true, maxVertexes, _2);
    maxVertexes = std::accumulate(polygon.cbegin(), polygon.cend(), 0, operation);
    out << maxVertexes << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void kuznetsov::getMin(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  if (polygon.empty())
  {
    throw std::invalid_argument("Polygon empty\n");
    return;
  }
  std::string cmd;
  in >> cmd;
  if (cmd == "AREA")
  {
    double minArea = getAreaPolygon(polygon[0]);
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinArea, false, minArea, _2);
    minArea = std::accumulate(polygon.cbegin() + 1, polygon.cend(), 0.0, operation);
    out << std::fixed << std::setprecision(1) << minArea << '\n';
  }
  else if (cmd == "VERTEXES")
  {
    size_t minVertexes = polygon[0].points.size();
    using namespace std::placeholders;
    auto operation = std::bind(getMaxOrMinVertexes, false, minVertexes, _2);
    minVertexes = std::accumulate(polygon.cbegin() + 1, polygon.cend(), 0, operation);
    out << minVertexes << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
}

void kuznetsov::getCount(std::vector< Polygon >& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  std::string cmd;
  in >> cmd;
  if (cmd == "EVEN")
  {
    size_t count = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getCountOfOddOrEvenVertexes, true, _1, _2);
    count += std::accumulate(polygon.cbegin(), polygon.cend(), count, operation);
    out << count << '\n';
  }
  else if (cmd == "ODD")
  {
    size_t count = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getCountOfOddOrEvenVertexes, false, _1, _2);
    count += std::accumulate(polygon.cbegin(), polygon.cend(), count, operation);
    out << count << '\n';
  }
  else if (std::all_of(cmd.cbegin(), cmd.cend(), ::isdigit))
  {
    size_t num = std::stoi(cmd);

    if (num < 3)
    {
      throw std::invalid_argument("The entered number of vertices must be greater than 3.\n");
    }

    size_t count = 0;
    using namespace std::placeholders;
    auto operation = std::bind(getCountWithNumVertexes, num, _1, _2);
    count += std::accumulate(polygon.cbegin(), polygon.cend(), 0, operation);
    out << count << '\n';
  }
  else
  {
    out << "<INVALID COMMAND>\n";
  }
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
  Point min;
  Point max;
  min = getFramePoint(false, min, polygon);
  max = getFramePoint(true, max, polygon);
  if (isInFrame(min, max, shape))
  {
    out << "<TRUE>\n";
  }
  else
  {
    out << "<FALSE>\n";
  }
}
