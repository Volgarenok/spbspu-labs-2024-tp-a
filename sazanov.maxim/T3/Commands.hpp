#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "Polygon.hpp"

namespace sazanov
{
  struct GetTotalPolygonsArea
  {
    using AccumulatePredicate = std::function< double(double, double) >;
    std::unordered_map< std::string, AccumulatePredicate > accumulatePredicates;
    using Filter = std::function< bool(const Polygon&) >;
    std::unordered_map< std::string, Filter > filters;
    std::unordered_map< std::string, bool > emptyVectorSupport;

    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  struct GetMaxValue
  {
    using Comparator = std::function< bool(const Polygon&, const Polygon&) >;
    using OutputValue = std::function< void(const Polygon&, std::ostream& out) >;
    std::unordered_map< std::string, std::pair< Comparator, OutputValue > > subCommands;

    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  struct GetMinValue
  {
    using Comparator = std::function< bool(const Polygon&, const Polygon&) >;
    using OutputValue = std::function< void(const Polygon&, std::ostream& out) >;
    std::unordered_map< std::string, std::pair< Comparator, OutputValue > > subCommands;

    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  struct CountPolygons
  {
    using Filter = std::function< bool(const Polygon&) >;
    std::unordered_map< std::string, Filter > subCommands;
    using NumberCommandPredicate = std::function< bool(const Polygon&, size_t) >;
    NumberCommandPredicate numberCommand;

    void operator()(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  };

  void getMaxSequence(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
  void countSamePolygons(const std::vector< Polygon >& vector, std::istream& in, std::ostream& out);
}

#endif
