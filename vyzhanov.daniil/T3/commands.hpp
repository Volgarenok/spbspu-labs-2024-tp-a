#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <vector>
#include "polygon.hpp"

namespace vyzhanov
{
  void area(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void max(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void min(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void count(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void lessarea(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void reacts(const std::vector< Polygon >&, std::istream&, std::ostream&);
  void rmecho(std::vector< Polygon >&, std::istream&, std::ostream&);

  bool isEven(const Polygon&);
  bool isOdd(const Polygon&);
  double getMeanArea(double, const Polygon&, size_t);
  double isNumVertexes(const Polygon&, size_t);
  bool compareArea(const Polygon&, const Polygon&);
  bool compareVertexes(const Polygon&, const Polygon&);
  bool isRectangle(const Polygon&);
  bool areSame(const Polygon&, const Polygon&, size_t&);

  struct RectangleVector
  {
    Point vertexes;
    RectangleVector(const Point&, const Point&);
    double operator*(const RectangleVector&);
    double getLength() const;
    double cos(const RectangleVector&);
  };
}

#endif
