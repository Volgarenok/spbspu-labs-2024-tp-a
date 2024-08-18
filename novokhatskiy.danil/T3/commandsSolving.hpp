#ifndef COMMANDS_SOLVING_HPP
#define COMMANDS_SOLVING_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include <StreamGuard.hpp>
#include "polygon.hpp"

namespace novokhatskiy
{
  namespace commands
  {
    void getAreaCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void getMinCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void getMaxCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void getCountCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void getPermsCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void getRectangleCmd(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out);
  }
}

#endif
