#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <exception>
#include <string>
#include "polygon.hpp"

namespace zaparin
{
  enum Type
  {
    Even, Odd, Mean, Vertexes
  };

  double getArea(const Polygon& plg);
  double getSpecificArea(const Polygon& plg, Type, size_t vertexes, size_t polygons);
  size_t getVertexes(const Polygon& plg);
  bool isRight(const Polygon& plg, Type, size_t vertexes);
  size_t isEqualCounter(const Polygon& plg, const std::vector< Point >& src, size_t& counter);
  bool isIntersected(const Polygon& plg, const std::vector< Point >& points);

  void cmdArea(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdMax(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdMin(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdCount(std::vector< Polygon >& plgs, std::istream&, std::ostream& out);
  void cmdMaxSeq(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdIntersections(std::vector< Polygon > plgs, std::istream& in, std::ostream& out);
}

#endif

