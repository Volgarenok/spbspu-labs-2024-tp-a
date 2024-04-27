#include "PolygonVectorFunctors.hpp"
#include <string>
#include <map>
#include <functional>
#include <numeric>
#include <exception>
#include <iostream>

double sazanov::GetTotalPolygonsArea::operator()(const std::vector<Polygon>& vector, const std::string& subCommand)
{
  std::map< std::string, std::function< double(double, const Polygon&) > > const_cmds;
  const_cmds["BASE"] = AccumulatePolygonArea{};
  using namespace std::placeholders;
  const_cmds["ODD"] = std::bind(AccumulatePolygonArea{}, _1, _2, true);
  const_cmds["EVEN"] = std::bind(AccumulatePolygonArea{}, _1, _2, false);

  double area = -1;
  try
  {
    area = std::accumulate(vector.begin(), vector.end(), 0.0, const_cmds.at(subCommand));
  }
  catch (const std::logic_error&)
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  return area;
}

double sazanov::AccumulatePolygonArea::operator()(double area, const sazanov::Polygon& polygon)
{
  area += polygon.getArea();
  return area;
}

double sazanov::AccumulatePolygonArea::operator()(double area, const sazanov::Polygon& polygon, bool isOdd)
{
  if (polygon.points.size() % 2 == isOdd)
  {
    area += AccumulatePolygonArea{}(area, polygon);
  }
  return area;
}

double sazanov::GetMeanPolygonsArea::operator()(const std::vector<Polygon>& vector)
{
  return GetTotalPolygonsArea{}(vector) / vector.size();
}
