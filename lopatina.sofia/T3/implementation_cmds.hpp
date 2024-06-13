#ifndef IMPLEMENTATION_CMDS_HPP
#define IMPLEMENTATION_CMDS_HPP

#include "polygon.hpp"
namespace lopatina
{
  double doAreaEven(const std::vector <Polygon> & figures);
  double doAreaOdd(const std::vector <Polygon> & figures);
  double doAreaMean(const std::vector <Polygon> & figures);
  double doAreaNum(const std::vector <Polygon> & figures, size_t num);
  double doMaxArea(const std::vector<Polygon> & figures);
  size_t doMaxVertexes(const std::vector<Polygon> & figures);
  double doMinArea(const std::vector<Polygon> & figures);
  size_t doMinVertexes(const std::vector<Polygon> & figures);
  size_t doCountEven(const std::vector<Polygon> & figures);
  size_t doCountOdd(const std::vector<Polygon> & figures);
  size_t doCountNum(const std::vector<Polygon> & figures, size_t num);

  size_t doMaxSeq(const std::vector<Polygon> & figures, const Polygon & given_figure);
  size_t doRmEcho(std::vector<Polygon> & figures, const Polygon & given_figure);
  size_t doRightShapes(const std::vector<Polygon> & figures);
}

#endif
