#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "polygon.hpp"
namespace lopatina
{
  void areaCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out);
  void maxCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out);
  void minCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out);
  void countCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out);
  void maxSeqCmd(const std::vector< Polygon > & figures, std::istream & in, std::ostream & out);
  void rmEchoCmd(std::vector< Polygon > & figures, std::istream & in, std::ostream & out);
  void rightShapesCmd(const std::vector< Polygon > & figures, std::ostream & out);
}

#endif
