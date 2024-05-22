#ifndef COMMANDS_SOLVING_HPP
#define COMMANDS_SOLVING_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include "polygon.hpp"

namespace novokhatskiy
{
  namespace commands
  {
    void commandArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    double doAccumulateNumOfVertexesArea(double res, size_t vertexes, const Polygon& polygons);
    double doAccumulateMeanArea(double res, const Polygon& p, const std::vector< Polygon >& polygons);
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

    double AccumulateMaxArea(double res, const Polygon& p);
    double AccumulateMinArea(double res, const Polygon& p);

    double doAccumulateEvenArea(double res, const Polygon& p);
    double doAccumulateOddArea(double res, const Polygon& p);

    void commandMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    void commandMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);

    size_t AccumulateMinVertexes(size_t size, const Polygon& p);
    size_t AccumulateMaxVertexes(size_t size, const Polygon& p);
    void commandCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    bool isEven(const Polygon& p);
    bool isOdd(const Polygon& p);
    bool areVertexes(const Polygon& p, size_t vertexes);
    bool checkPerms(Polygon& p1, Polygon& p2);
    void commandPerms(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
    bool checkRectangle(const Polygon& p);
    void commandRectangle(const std::vector< Polygon >& polygons, std::istream&, std::ostream& out);
  }
}

#endif
