#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <exception>
#include <string>
#include "polygon.hpp"

namespace zaparin
{
  struct InvalidCommand : public std::exception
  {
    const char* what()
    {
      return "<INVALID COMMAND>";
    }
  };

  enum Type
  {
    Even, Odd, Mean, Vertexes
  };
  


  double getArea(const Polygon& plg);
  double getSpecificArea(const Polygon& plg, Type, size_t vertexes, size_t polygons);
  size_t getVertexes(const Polygon& plg);
  bool isRight(const Polygon& plg, Type, size_t vertexes);

  void cmdArea(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdMax(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdMin(std::vector< Polygon >& plgs, std::istream& in, std::ostream& out);
  void cmdCount(std::vector< Polygon >& plgs, std::istream&, std::ostream& out);
  void cmdMaxSeq(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out);
  void cmdIntersections(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out);
}

#endif
