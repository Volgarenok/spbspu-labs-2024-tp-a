#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <numeric>
#include <algorithm>

#include "polygon.hpp"

namespace gladyshev
{
  void findAreas(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void findMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void findMin(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void processCount(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void findLessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys);
  void processEcho(std::istream& in, std::ostream& out, std::vector< Polygon >& polys);
  bool compareArea(const Polygon& left, const Polygon& right);
  bool comparePoints(const Polygon& left, const Polygon& right);
  size_t countNum(const std::vector< Polygon >& polys, size_t n);
  size_t countEven(const std::vector< Polygon >& polys);
  size_t countOdd(const std::vector< Polygon >& polys);
  bool checkVerts(const Polygon& poly, size_t n);
  bool isEvenOdd(const Polygon& poly);
  template < typename pred >
  double mainSum(const std::vector< Polygon >& polys, pred p)
  {
    std::vector < Polygon > temp;
    std::copy_if(polys.begin(), polys.end(), std::back_inserter(temp), p);
    std::vector< double > areas;
    std::transform(temp.begin(), temp.end(), std::back_inserter(areas), findArea);
    return std::accumulate(areas.begin(), areas.end(), 0.0);
  }
}

#endif
