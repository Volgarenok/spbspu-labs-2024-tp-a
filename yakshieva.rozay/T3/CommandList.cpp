#include "CommandList.hpp"
#include <algorithm>
#include <functional>

bool yakshieva::PolygonComparator::operator()(const Polygon& p1, const Polygon& p2) const
{
  return p1 == p2 && p2 == target;
}

size_t yakshieva::removeConsecutiveDuplicates(std::vector< Polygon >& polygons, const Polygon& target)
{
  PolygonComparator comparator{ target };
  std::size_t removedCount = 0;
  auto it = std::adjacent_find(polygons.begin(), polygons.end(), std::bind(comparator, std::placeholders::_1, std::placeholders::_2));
  while (it != polygons.end())
  {
    it = polygons.erase(it);
    ++removedCount;
    it = std::adjacent_find(it, polygons.end(), std::bind(comparator, std::placeholders::_1, std::placeholders::_2));
  }
  return removedCount;
}

yakshieva::Polygon yakshieva::EntryDuplicator::operator()(Polygon&& rhs)
{
  if (arg == rhs)
  {
    vec.emplace_back(rhs);
  }
  return std::move(rhs);
}

void yakshieva::duplicateEntries(std::vector< Polygon >& p, const Polygon& targetP)
{
  EntryDuplicator duplicator{ p, targetP };
  std::vector< Polygon > result;
  auto moveIt = std::make_move_iterator< std::vector< Polygon >::iterator >;
  std::transform(moveIt(p.begin()), moveIt(p.end()), std::back_inserter(result), std::ref(duplicator));
  p = std::move(result);
}
