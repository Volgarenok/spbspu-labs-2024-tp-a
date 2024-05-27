#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>

#include "polygon.hpp"

namespace gladyshev
{
  void findAreas(std::istream& in, const std::vector< Polygon > polys);
  void findMax(std::istream& in, const std::vector< Polygon > polys);
  void findMin(std::istream& in, const std::vector< Polygon > polys);
  void processCount(std::istream& in, const std::vector< Polygon > polys);
  void findLessArea(std::istream& in, const std::vector< Polygon > polys);
  void processEcho(std::istream& in, const std::vector< Polygon > polys);
  double findEven(const std::vector< Polygon >& polys);
  double findOdd(const std::vector< Polygon >& polys);
  double findMean(const std::vector< Polygon >& polys);
  double findAreaCount(const std::vector< Polygon >& polys, size_t n);
  size_t countEven(const std::vector< Polygon >& polys);
  size_t countOdd(const std::vector< Polygon >& polys);
}

#endif
