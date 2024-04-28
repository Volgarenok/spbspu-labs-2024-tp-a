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
    out << std::accumulate(vector.begin(), vector.end(), 0.0, subCommands[subCommandKey]);
  }
  catch (...)
  {
    std::cout << "<INVALID COMMAND>\n";
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

void sazanov::GetMaxValue::operator()(const std::vector<Polygon>& vector, GetMaxValueFunctor*, std::ostream& out)
{
  std::max_element(vector.begin(), vector.end(), [](const Polygon& x, const Polygon& y) {return x.getArea() < y.getArea();});

}

double sazanov::AccumulateMaxMinArea::operator()(double area, const sazanov::Polygon& polygon)
{
  return 0;
}
