#include "CommandFunctors.hpp"
#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "Polygon.hpp"
#include "StreamGuard.hpp"

void sazanov::GetTotalPolygonsArea::operator()(const std::vector<Polygon>& vector, const std::string& subCommandKey, std::ostream& out)
{
  AccumulateFunctor accumulateFunctor;
  try
  {
    accumulateFunctor = subCommands.at(subCommandKey);
  }
  catch (const std::out_of_range&)
  {
    std::size_t number = std::stoull(subCommandKey);
    using namespace std::placeholders;
    accumulateFunctor = std::bind(numberCommand, _1, _2, number);
  }
  StreamGuard guard(std::cout);
  std::cout << std::setprecision(1) << std::fixed;
  out << std::accumulate(vector.begin(), vector.end(), 0.0, accumulateFunctor);
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
    area += polygon.getArea();
  }
  return area;
}

double sazanov::AccumulateAreaWithNumOfVertexes::operator()(double area, const Polygon& polygon, std::size_t numOfVertexes)
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
  StreamGuard guard(std::cout);
  std::cout << std::setprecision(1) << std::fixed;
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

void sazanov::CountPolygons::operator()(const std::vector<Polygon>& vector, const std::string& subCommandKey, std::ostream& out)
{
  CountFunctor countFunctor;
  try
  {
    countFunctor = subCommands.at(subCommandKey);
  }
  catch (const std::out_of_range&)
  {
    std::size_t number = std::stoull(subCommandKey);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    countFunctor = std::bind(numberCommand, _1, number);
  }
  out << std::count_if(vector.cbegin(), vector.cend(), countFunctor);
}

bool sazanov::CountWithParity::operator()(const sazanov::Polygon& polygon, bool isOdd)
{
  return polygon.points.size() % 2 == isOdd;
}

bool sazanov::CountWithNumOfVertexes::operator()(const Polygon& polygon, std::size_t numOfVertexes)
{
  return polygon.points.size() == numOfVertexes;
}
