#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <vector>
#include <functional>
#include "polygon.hpp"

namespace baranov
{
  void area(std::vector< Polygon > &, std::istream &, std::ostream &);

  class AreaCounter
  {
    public:
      explicit AreaCounter(const Point &);
      double operator()(double currArea, const Point & b, const Point & c);
    private:
      Point a_;
  };
  double getArea(const Polygon & polygon);
  double countMeanArea(double currArea, const Polygon & polygon, size_t count);
  double sumArea(double area, const Polygon & polygon, std::function< bool(const Polygon &) > p);
  bool isEven(const Polygon & polygon);
  bool isOdd(const Polygon & polygon);
  bool isNumOfVertexes(const Polygon & polygon, size_t numOfVertexes);
}

#endif

