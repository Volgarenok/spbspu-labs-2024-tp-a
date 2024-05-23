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
    void commandArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void commandMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void commandMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void commandCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void commandRectangle(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out);
    void commandPerms(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  }
}

#endif
