#ifndef POLYGON_HANDLER_HPP
#define POLYGON_HANDLER_HPP

#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#include "polygon.hpp"

namespace kravchenko
{
  class PolygonHandler
  {
  public:
    void inputPolygons(std::istream& in);
    void handleCommands(std::istream& cmdIn, std::ostream& cmdOut);

  private:
    std::vector< kravchenko::Polygon > data_;
    static const std::map< std::string,
                           std::function< void(std::vector< kravchenko::Polygon >&, std::istream&, std::ostream&) > >&
    getCommandsMap();
  };

  class InvalidCommand: public std::exception
  {
  public:
    const char* what() const noexcept override;
  };
}

#endif