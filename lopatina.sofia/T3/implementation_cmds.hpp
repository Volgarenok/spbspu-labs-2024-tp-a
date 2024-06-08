#ifndef IMPLEMENTATION_CMDS_HPP
#define IMPLEMENTATION_CMDS_HPP

#include "polygon.hpp"
namespace lopatina
{
  void areaEven(const std::vector <Polygon> & figures);
  void areaOdd(const std::vector <Polygon> & figures);
  void areaMean(const std::vector <Polygon> & figures);
  void areaNum(const std::vector <Polygon> & figures, size_t num);
  void maxArea(const std::vector<Polygon> & figures);
  void maxVertexes(const std::vector<Polygon> & figures);
  void minArea(const std::vector<Polygon> & figures);
  void minVertexes(const std::vector<Polygon> & figures);
  void countEven(const std::vector<Polygon> & figures);
  void countOdd(const std::vector<Polygon> & figures);
  void countNum(const std::vector<Polygon> & figures, size_t num);
}

#endif
