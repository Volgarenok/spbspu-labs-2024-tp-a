#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "polygon.hpp"

namespace rebdev
{
  using polyVec = std::vector< rebdev::Polygon >;

  void areaEven(const polyVec & p, std::istream & in, std::ostream & out);
  void areaOdd(const polyVec & p, std::istream & in, std::ostream & out);
  void areaMean(const polyVec & p, std::istream & in, std::ostream & out);
  void areaNum(size_t s, const polyVec & p, std::istream & in, std::ostream & out);
  void maxArea(const polyVec & p, std::istream & in, std::ostream & out);
  void maxVertexes(const polyVec & p, std::istream & in, std::ostream & out);
  void minArea(const polyVec & p, std::istream & in, std::ostream & out);
  void minVertexes(const polyVec & p, std::istream & in, std::ostream & out);
  void countEven(const polyVec & p, std::istream & in, std::ostream & out);
  void countOdd(const polyVec & p, std::istream & in, std::ostream & out);
  void countNum(size_t s, const polyVec & p, std::istream & in, std::ostream & out);
  void rects(const polyVec & p, std::istream & in, std::ostream & out);
  void inframe(const polyVec & p, std::istream & in, std::ostream & out);

  double getArea(const Polygon & p);
}

#endif
