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
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygons), std::bind(isCorrectSizeFigure, std::placeholders::_1, std::stoi(argument)));
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
  output << std::setprecision(1) << std::fixed << sum << "\n";
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
