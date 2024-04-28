#include "CommandFunctors.hpp"
#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include "Polygon.hpp"

void sazanov::GetTotalPolygonsArea::operator()(const std::vector<Polygon>& vector, const std::string& subCommandKey, std::ostream& out)
{
  try
  {
    out << std::accumulate(vector.begin(), vector.end(), 0.0, subCommands.at(subCommandKey));
  }
  catch (std::out_of_range&)
  {
    out << "<INVALID COMMAND>\n";
  }
}

double sazanov::AccumulateArea::operator()(double area, const Polygon& polygon)
{
  area += polygon.getArea();
  return area;
}

double sazanov::AccumulateArea::operator()(double area, const Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += AccumulateArea{}(area, polygon);
  }
  return area;
}

double sazanov::AccumulateAreaWithNumOfVertexes::operator()(double area, const Polygon& polygon)
{
  if (polygon.points.size()  == numOfVertexes)
  {
    area += AccumulateArea{}(area, polygon);
  }
  return area;
}

double sazanov::AccumulateMeanArea::operator()(double area, const Polygon& polygon)
{
  return area + (polygon.getArea() / numOfPolygons);
}

void sazanov::GetMaxValue::operator()(const std::vector<Polygon>& vector, const std::string& subCommandKey, std::ostream& out)
{
  Comparator comp = subCommands[subCommandKey].first;
  OutputValue outputValue = subCommands[subCommandKey].second;

  outputValue(*std::max_element(vector.cbegin(), vector.cend(), comp), out);
}

bool sazanov::AreaComparator::operator()(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  return lhs.getArea() < rhs.getArea();
}

bool sazanov::VertexComparator::operator()(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  return lhs.points.size() < rhs.points.size();
}

void sazanov::OutputArea::operator()(const Polygon& polygon, std::ostream& out)
{
  out << polygon.getArea();
}

void sazanov::OutputVertex::operator()(const Polygon& polygon, std::ostream& out)
{
  out << polygon.points.size();
}

void sazanov::GetMinValue::operator()(const std::vector<Polygon>& vector, const std::string& subCommandKey, std::ostream& out)
{
  Comparator comp = subCommands[subCommandKey].first;
  OutputValue outputValue = subCommands[subCommandKey].second;

  outputValue(*std::min_element(vector.cbegin(), vector.cend(), comp), out);
}
