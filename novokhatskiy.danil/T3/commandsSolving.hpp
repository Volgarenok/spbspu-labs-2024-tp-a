#ifndef COMMANDS_SOLVING_HPP
#define COMMANDS_SOLVING_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include "StreamGuard.hpp"
#include "polygon.hpp"

namespace novokhatskiy
{
  void commandArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  double AccumulateNumOfVertexesArea(double res, size_t vertexes, const Polygon& polygons); //size_t numOfVertexes
  double AccumulateEvenOrOddArea(double res,const Polygon& p, bool isEven);
  double AccumulateMeanArea(double res, const Polygon& p);
  struct AccumulateArea
  {
    novokhatskiy::Point p1;
    double operator()(double& res, const novokhatskiy::Point& p2, const novokhatskiy::Point& p3)
    {
      res += 0.5 * (std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)));
      p1 = p2;
      return res;
    }
  };
}

#endif
