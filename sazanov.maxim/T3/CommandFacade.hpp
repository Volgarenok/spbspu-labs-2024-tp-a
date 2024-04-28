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
    using SubCommandFunctor = std::function< double(double, const Polygon&) >;
    using SubCommands = std::unordered_map< std::string, SubCommandFunctor >;
    using CommandFunctor = std::function< void(std::string, std::ostream& out) >;

  public:
    explicit CommandFacade(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void nextCommand();

  private:
    const std::vector< Polygon >& polygons_;
    std::istream& in_;
    std::ostream& out_;
    std::unordered_map< std::string, CommandFunctor > commands_;

    void addAreaSubCommands(SubCommands& area);
  };
}

#endif //COMMAND_CENTER_HPP
