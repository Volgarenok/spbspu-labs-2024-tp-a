#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Polygon.hpp"

namespace kozlova
{
  void generalArea(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  double getAreaEven(const std::vector<Polygon>& polygons);
  double getAreaOdd(const std::vector<Polygon>& polygons);
  double getAreaMean(const std::vector<Polygon>& polygons);
  double getAreaNum(const std::vector<Polygon>& polygons, size_t number);

  void generalMax(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  double getAreaMax(const std::vector<Polygon>& polygons);
  size_t getVertexesMax(const std::vector<Polygon>& polygons);
  void generalMin(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  double getAreaMin(const std::vector<Polygon>& polygons);
  size_t getVertexesMin(const std::vector<Polygon>& polygons);

  void generalCount(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  size_t getCountEven(const std::vector<Polygon>& polygons);
  size_t getCountOdd(const std::vector<Polygon>& polygons);
  size_t getCountNum(const std::vector<Polygon>& polygons, size_t number);

  void generalPerms(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  void generalRmEcho(std::vector<Polygon>& polygons, std::istream& in, std::ostream& out);
  void generalRightShapes(const std::vector<Polygon>& polygons, std::ostream& out);
}


#endif
