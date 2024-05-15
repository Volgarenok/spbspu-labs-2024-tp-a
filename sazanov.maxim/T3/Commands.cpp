#include "Commands.hpp"
#include <numeric>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <StreamGuard.hpp>
#include "CommandPredicates.hpp"
#include "Polygon.hpp"

void sazanov::GetTotalPolygonsArea::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  AccumulatePredicate accumulateFunctor;
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
    size_t number = std::stoull(subCommandKey);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    accumulateFunctor = std::bind(numberCommand, _1, _2, number);
  }
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  out << std::accumulate(vector.cbegin(), vector.cend(), 0.0, accumulateFunctor);
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
    size_t number = std::stoull(subCommandKey);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    countFunctor = std::bind(numberCommand, _1, number);
  }
  out << std::count_if(vector.cbegin(), vector.cend(), countFunctor);
}

void sazanov::getMaxSequence(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
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

  using namespace std::placeholders;
  out << std::accumulate(vector.cbegin(), vector.cend(), 0.0, std::bind(accumulatePolygonSequence{}, _1, _2, polygon));
}

void sazanov::countSamePolygons(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in)
  {
    throw std::logic_error("invalid polygon");
  }

  using namespace std::placeholders;
  out << std::count_if(vector.cbegin(), vector.cend(), std::bind(isSamePolygons, polygon, _1));
}
