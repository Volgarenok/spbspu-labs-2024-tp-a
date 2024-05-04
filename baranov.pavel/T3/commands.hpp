#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include "polygon.hpp"

namespace baranov
{
  void area(std::vector< Polygon > & shapes, std::istream & in, std::ostream &);
  void areaEven(std::vector< Polygon > & shapes, std::istream & in, std::ostream &out);
  void areaOdd(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
  void areaMean(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out);
}

#endif

