#ifndef COMMAND_CENTER_HPP
#define COMMAND_CENTER_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <numeric>
#include <exception>
#include <iostream>
#include "Polygon.hpp"
#include "CommandFunctors.hpp"

namespace sazanov
{
  class CommandFacade
  {
    using AccumulateFunctor = std::function< double(double, const Polygon&) >;
    using AreaSubCommands = std::unordered_map< std::string, AccumulateFunctor >;

    using Comparator = std::function< bool(const Polygon&, const Polygon&) >;
    using OutputValueFunctor = std::function< void(const Polygon&, std::ostream& out) >;
    using MaxMinSubCommands = std::unordered_map<std::string, std::pair<Comparator, OutputValueFunctor>>;

    using CountFunctor = std::function< bool(const Polygon&) >;
    using CountSubCommands = std::unordered_map<std::string, CountFunctor>;

  public:
    explicit CommandFacade(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void nextCommand();

  private:
    const std::vector< Polygon >& polygons_;
    std::istream& in_;
    std::ostream& out_;
    using CommandFunctor = std::function< void(std::string, std::ostream& out) >;
    std::unordered_map< std::string, CommandFunctor > commands_;

    AreaSubCommands getAreaSubCommands();
    MaxMinSubCommands getMaxMinSubCommands();
    CountSubCommands getCountSubcommands();
  };
}

#endif
