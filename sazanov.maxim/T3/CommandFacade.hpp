#ifndef COMMAND_FACADE_HPP
#define COMMAND_FACADE_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <numeric>
#include <exception>
#include <iostream>
#include "Polygon.hpp"
#include "Commands.hpp"

namespace sazanov
{
  class CommandFacade
  {
    using AccumulatePredicate = std::function< double(double, const Polygon&) >;
    using AreaSubCommands = std::unordered_map< std::string, AccumulatePredicate >;

    using Comparator = std::function< bool(const Polygon&, const Polygon&) >;
    using OutputValuePredicate = std::function< void(const Polygon&, std::ostream& out) >;
    using MaxMinSubCommands = std::unordered_map< std::string, std::pair< Comparator, OutputValuePredicate > >;

    using CountPredicate = std::function< bool(const Polygon&) >;
    using CountSubCommands = std::unordered_map< std::string, CountPredicate >;

  public:
    explicit CommandFacade(const std::vector< Polygon >& polygons);
    void nextCommand(std::istream& in, std::ostream& out) const;

  private:
    const std::vector< Polygon >& polygons_;

    using CommandFunctor = std::function< void(std::istream& in, std::ostream& out) >;
    std::unordered_map< std::string, CommandFunctor > commands_;

    AreaSubCommands getAreaSubCommands() const;
    MaxMinSubCommands getMaxMinSubCommands() const;
    CountSubCommands getCountSubcommands() const;
    std::unordered_map< std::string, bool > getEmptyVectorSupportInfo() const;
  };
}

#endif
