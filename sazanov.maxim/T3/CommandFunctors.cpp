#include "CommandFunctors.hpp"
#include <string>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <StreamGuard.hpp>
#include "Polygon.hpp"

void sazanov::GetTotalPolygonsArea::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  AccumulateFunctor accumulateFunctor;
  std::string subCommandKey;
  in >> subCommandKey;
  try
  {
    accumulateFunctor = subCommands.at(subCommandKey);
    if (!emptyVectorSupport[subCommandKey] && vector.empty())
    {
      throw std::logic_error("empty vector");
    }
  }
  catch (const std::out_of_range&)
  {
    std::size_t number = std::stoull(subCommandKey);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    accumulateFunctor = std::bind(numberCommand, _1, _2, number);
  }
  StreamGuard guard(std::cout);
  std::cout << std::setprecision(1) << std::fixed;
  out << std::accumulate(vector.cbegin(), vector.cend(), 0.0, accumulateFunctor);
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
    area += polygon.getArea();
  }
  return area;
}

double sazanov::AccumulateMeanArea::operator()(double area, const Polygon& polygon)
{
  return area + (polygon.getArea() / numOfPolygons);
}

void sazanov::GetMaxValue::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  if (vector.empty())
  {
    throw std::logic_error("empty vector");
  }
  std::string subCommandKey;
  in >> subCommandKey;

  Comparator comp = subCommands.at(subCommandKey).first;
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

void sazanov::GetMinValue::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  if (vector.empty())
  {
    throw std::logic_error("empty vector");
  }
  std::string subCommandKey;
  in >> subCommandKey;

  Comparator comp = subCommands.at(subCommandKey).first;
  OutputValue outputValue = subCommands[subCommandKey].second;

  outputValue(*std::min_element(vector.cbegin(), vector.cend(), comp), out);
}

void sazanov::CountPolygons::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  CountFunctor countFunctor;
  std::string subCommandKey;
  in >> subCommandKey;
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

void sazanov::GetMaxSequence::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  if (vector.empty())
  {
    throw std::logic_error("empty vector");
  }

  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("invalid polygon");
  }

  std::size_t maxSequence = 0;
  std::accumulate(vector.cbegin(), vector.cend(), 0.0, AccumulatePolygonSequence{polygon, maxSequence});
  out << maxSequence;
}

std::size_t sazanov::AccumulatePolygonSequence::operator()(std::size_t sequence, const sazanov::Polygon& polygon)
{
  if (polygon == commandPolygon)
  {
    ++sequence;
  }
  else
  {
    sequence = 0;
  }
  maxSequence = std::max(sequence, maxSequence);
  return sequence;
}

void sazanov::CountSamePolygons::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("invalid polygon");
  }

  using namespace std::placeholders;
  out << std::count_if(vector.cbegin(), vector.cend(), std::bind(IsSamePolygons{}, polygon, _1));
}

bool sazanov::IsSamePolygons::operator()(const sazanov::Polygon& lhs, const sazanov::Polygon& rhs)
{
  if (rhs.points.size() != lhs.points.size())
  {
    return false;
  }
  Polygon sortedLhs = lhs;
  std::sort(sortedLhs.points.begin(), sortedLhs.points.end(), PointComparator{});

  Polygon sortedRhs = rhs;
  std::sort(sortedRhs.points.begin(), sortedRhs.points.end(), PointComparator{});

  int xDiff = sortedLhs.points.front().x - sortedRhs.points.front().x;
  int yDiff = sortedLhs.points.front().y - sortedRhs.points.front().y;

  using namespace std::placeholders;
  return std::equal(sortedLhs.points.cbegin(), sortedLhs.points.cend(), sortedRhs.points.cbegin(),
    std::bind(IsEqualPointDiff{}, _1, _2, xDiff, yDiff));
}

bool sazanov::IsEqualPointDiff::operator()(const Point& lhs, const Point& rhs, int xDiff, int yDiff)
{
  return lhs.x - rhs.x == xDiff && lhs.y - rhs.y == yDiff;
}

bool sazanov::PointComparator::operator()(const sazanov::Point& lhs, const sazanov::Point& rhs)
{
  if (lhs.x != rhs.x)
  {
    return lhs.x < rhs.x;
  }
  return lhs.y < rhs.y;
}
