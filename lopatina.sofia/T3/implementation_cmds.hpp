#ifndef IMPLEMENTATION_CMDS_HPP
#define IMPLEMENTATION_CMDS_HPP

#include "polygon.hpp"
namespace lopatina
{
  double areaEven(const std::vector <Polygon> & figures);
  double areaOdd(const std::vector <Polygon> & figures);
  double areaMean(const std::vector <Polygon> & figures);
  double areaNum(const std::vector <Polygon> & figures, size_t num);
  double maxArea(const std::vector<Polygon> & figures);
  size_t maxVertexes(const std::vector<Polygon> & figures);
  double minArea(const std::vector<Polygon> & figures);
  size_t minVertexes(const std::vector<Polygon> & figures);
  size_t countEven(const std::vector<Polygon> & figures);
  size_t countOdd(const std::vector<Polygon> & figures);
  size_t countNum(const std::vector<Polygon> & figures, size_t num);
}

#endif
