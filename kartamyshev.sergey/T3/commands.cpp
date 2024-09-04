#include "commands.h"

#include <functional>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <string>

#include "Polygon.h"


bool isOdd(const kartamyshev::Polygon& polygon)
{
  return polygon.points.size() % 2;
}

bool isEven(const kartamyshev::Polygon& polygon)
{
  return !(polygon.points.size() % 2);
}

bool isCorrectSizeFigure(const kartamyshev::Polygon& polygon, size_t size)
{
  return polygon.points.size() == size;
}

bool comparerVertexes(const kartamyshev::Polygon& polygon1, const kartamyshev::Polygon& polygon2)
{
  return polygon1.points.size() < polygon2.points.size();
}

bool compareArea(const kartamyshev::Polygon& first, const kartamyshev::Polygon& second)
{
  return getArea(first) < getArea(second);
}

kartamyshev::Point overlay(const kartamyshev::Point& first, const kartamyshev::Point& second)
{
  return kartamyshev::Point{ second.x - first.x, second.y - first.y };
}

void kartamyshev::area(const std::vector<Polygon>& data, std::istream& input, std::ostream& output)
{
  output << std::setprecision(1) << std::fixed;
  std::string argument;
  input >> argument;
  std::vector< Polygon > polygons;
  if (argument == "EVEN")
  {
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(polygons), isEven);
  }
  else if (argument == "ODD")
  {
    std::copy_if(data.cbegin(), data.cend(), std::back_inserter(polygons), isOdd);
  }
  else if (argument == "MEAN")
  {
    if (data.size() == 0)
    {
      throw std::logic_error("Irregular polygon");
    }
    else
    {
      std::copy(data.cbegin(), data.cend(), std::back_inserter(polygons));
    }
  }
  else if (std::stoi(argument) > 2)
  {
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygons),
    std::bind(isCorrectSizeFigure, std::placeholders::_1, std::stoi(argument)));
  }
  else
  {
    throw std::exception();
  }
  std::vector < double > areas(polygons.size());
  std::transform(polygons.cbegin(), polygons.cend(), areas.begin(), getArea);
  double sum = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
  if (argument == "MEAN")
  {
    sum /= polygons.size();
  }
  output << std::setprecision(1) << std::fixed << sum;
}

void kartamyshev::min(const std::vector< kartamyshev::Polygon >& data, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string argument;
  input >> argument;
  if (data.size() == 0)
  {
    throw std::logic_error("Empty polygon");
  }
  else
  {
    if (argument == "AREA")
    {
      output << getArea(*std::min_element(data.cbegin(), data.cend(), compareArea));
    }
    else if (argument == "VERTEXES")
    {
      output << (*std::min_element(data.cbegin(), data.cend(), comparerVertexes)).points.size();
    }
    else
    {
      output << "Wrong argument";
    }
  }
}

void kartamyshev::max(const std::vector< kartamyshev::Polygon >& data, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string argument;
  input >> argument;
  if (data.size() == 0)
  {
    throw std::logic_error("Empty polygon");
  }
  else
  {
    if (argument == "AREA")
    {
      output << getArea(*std::max_element(data.cbegin(), data.cend(), compareArea));
    }
    else if (argument == "VERTEXES")
    {
      output << (*std::max_element(data.cbegin(), data.cend(), comparerVertexes)).points.size();
    }
    else
    {
      output << "Wrong argument";
    }
  }
}

void kartamyshev::count(const std::vector<Polygon>& data, std::istream& input, std::ostream& output)
{
  output << std::fixed << std::setprecision(1);
  std::string argument;
  input >> argument;
  if (argument == "EVEN")
  {
    output << std::count_if(data.cbegin(), data.cend(), isEven);
  }
  else if (argument == "ODD")
  {
    output << std::count_if(data.cbegin(), data.cend(), isOdd);
  }
  else
  {
    size_t countVertex = 0;
    countVertex = std::stoull(argument);
    if (countVertex < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    else
    {
      std::function< bool(const Polygon&) > isRightCount = std::bind(isCorrectSizeFigure, std::placeholders::_1, countVertex);
      output << std::count_if(data.begin(), data.end(), isRightCount);
    }
  }
}

bool isSame(kartamyshev::Polygon first, kartamyshev::Polygon second)
{
  if (first.points.size() != second.points.size())
  {
    return false;
  }
  std::vector< kartamyshev::Point > firstDiffs(first.points.size() - 1);
  std::vector< kartamyshev::Point > secondDiffs(first.points.size() - 1);
  using namespace std::placeholders;
  std::transform(first.points.cbegin() + 1, first.points.cend(), firstDiffs.begin(), std::bind(overlay, _1, first.points[0]));
  std::transform(second.points.cbegin() + 1, second.points.cend(), secondDiffs.begin(), std::bind(overlay, _1, second.points[0]));
  return (firstDiffs == secondDiffs);
}

void kartamyshev::same(const std::vector< Polygon >& data, std::istream& input, std::ostream& output)
{
  kartamyshev::Polygon argument;
  input >> argument;
  if (!input || input.peek() != '\n')
  {
    throw std::exception();
  }
  using namespace std::placeholders;
  output << std::count_if(data.cbegin(), data.cend(), std::bind(isSame, _1, argument));
}

bool checkRectangle(const kartamyshev::Polygon& dot)
{
  if (dot.points.size() != 4)
  {
    return false;
  }
  kartamyshev::Rectangle firstSide(dot.points[0], dot.points[1]);
  kartamyshev::Rectangle secondSide(dot.points[1], dot.points[2]);
  kartamyshev::Rectangle thirdSide(dot.points[2], dot.points[3]);
  kartamyshev::Rectangle fourthSide(dot.points[0], dot.points[3]);
  return (firstSide.cos(secondSide) == 0) &&
    (secondSide.cos(thirdSide) == 0) &&
    (thirdSide.cos(fourthSide) == 0);
}

void kartamyshev::rects(const std::vector< kartamyshev::Polygon >& polygons, std::ostream& output)
{
  output << std::count_if(polygons.cbegin(), polygons.cend(), checkRectangle) << '\n';
}
