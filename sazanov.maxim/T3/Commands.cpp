#include "Commands.hpp"
#include <numeric>
#include <iostream>
#include <algorithm>
#include "DoubleO.hpp"
#include "CommandPredicates.hpp"
#include "Polygon.hpp"

void sazanov::GetTotalPolygonsArea::operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{

  std::string subCommandKey;
  in >> subCommandKey;
  AccumulatePredicate accumulatePredicate;
  Filter filter;
  try
  {
    accumulatePredicate = accumulatePredicates.at(subCommandKey);
    filter = filters.at(subCommandKey);
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
    accumulatePredicate = std::plus< double >();
    filter = std::bind(isEqualNumOfVertexes, _1, number);
  }

  const std::vector< Polygon >* filtered = &vector;
  std::vector< Polygon > temp;
  if (filter != nullptr)
  {
    std::copy_if(vector.cbegin(), vector.cend(), std::inserter(temp, temp.begin()), filter);
    filtered = &temp;
  }

  std::vector< double > areas(filtered->size());
  std::transform(filtered->cbegin(), filtered->cend(), std::back_inserter(areas), getArea);
  out << DoubleO{std::accumulate(areas.cbegin(), areas.cend(), 0.0, accumulatePredicate)};
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
  Filter filter;
  std::string subCommandKey;
  in >> subCommandKey;
  try
  {
    filter = subCommands.at(subCommandKey);
  }
  catch (const std::out_of_range&)
  {
    size_t number = std::stoull(subCommandKey);
    if (number < 3)
    {
      throw std::logic_error("invalid size");
    }
    using namespace std::placeholders;
    filter = std::bind(numberCommand, _1, number);
  }
  out << std::count_if(vector.cbegin(), vector.cend(), filter);
}

void sazanov::getMaxSequence(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  if (vector.empty())
  {
    throw std::logic_error("empty vector");
  }

  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::logic_error("invalid polygon");
  }

  std::vector< size_t > sequenceHistory;
  sequenceHistory.reserve(vector.size());
  using namespace std::placeholders;
  std::transform(vector.cbegin(), vector.cend(), std::back_inserter(sequenceHistory),
    std::bind(getNumberInSequence, _1, polygon, std::cref(sequenceHistory)));
  out << *std::max_element(sequenceHistory.begin(), sequenceHistory.end());
}

void sazanov::countSamePolygons(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (!in || in.peek() != '\n')
  {
    throw std::logic_error("invalid polygon");
  }

  using namespace std::placeholders;
  out << std::count_if(vector.cbegin(), vector.cend(), std::bind(isSamePolygons, polygon, _1));
}
