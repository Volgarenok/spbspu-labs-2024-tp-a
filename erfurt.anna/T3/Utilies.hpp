#ifndef UTILIES_HPP
#define UTILIES_HPP

#include "Polygon.hpp"

namespace erfurt
{
  double areaNum(const std::vector<Polygon> & poly, size_t num);
  double areaEven(const std::vector<Polygon> & poly);
  double areaOdd(const std::vector<Polygon> & poly);
  double areaMean(const std::vector<Polygon> & poly);
  void maxArea(const std::vector< Polygon > & poly, std::ostream & out);
  void maxVertexes(const std::vector< Polygon > & poly, std::ostream & out);
  void minArea(const std::vector< Polygon > & poly, std::ostream & out);
  void minVertexes(const std::vector< Polygon > & poly, std::ostream & out);
  bool isEvenVertexes(const Polygon & poly);
  bool isOddVertexes(const Polygon & poly);
  bool isNumVertexes(const Polygon & poly, size_t num);
  bool isPerm(const Polygon & poly1, const Polygon & poly2);
  bool isIndenticalPoly(const Polygon & poly1, const Polygon & poly2, const Polygon & poly);
}

#endif
