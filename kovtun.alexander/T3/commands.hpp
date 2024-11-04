#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>

#include "polygon.hpp"


namespace kovtun
{
  void area(const std::vector< kovtun::Polygon > & polygons, std::istream & in, std::ostream & out);
}

#endif
