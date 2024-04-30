#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Delimeter.hpp"
#include "Polygon.hpp"
#include "StreamGuard.hpp"

#include <algorithm>
#include <map>
#include <functional>

namespace erfurt
{
  //[AREA <EVEN|ODD>]
  struct AccumulateAreaParity
  {
    double operator()(double area, const Polygon & poly, bool isEven);
  };
  void accAreaParityEven(const std::vector<Polygon> & polygons, std::ostream & out);
  void accAreaParityOdd(const std::vector<Polygon> & polygons, std::ostream & out);

  //[AREA <MEAN>]
  struct AccumulateAreaMean
  {
    std::size_t count;
    double operator()(double area, const Polygon & poly);
  };
  void accAreaMean(const std::vector<Polygon> & polygons, std::ostream & out);

  //[AREA <num-of-vertexes>]
  struct AccumulateAreaNumOfVertex
  {
    std::size_t numOfVertex;
    double operator()(double area, const Polygon & poly);
  };
  void accAreaNumOfVertex(const std::vector<Polygon> & polygons, std::ostream & out, std::size_t numOfVertex);

  //AREA полностью
  void area(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);

  //[MAX <AREA>]
  struct AccumulateMaxArea
  {
    double operator()(double area, const Polygon & poly);
  };
  void accMaxArea(const std::vector<Polygon> & polygons, std::ostream & out);

  //[MAX <VERTEXES>
  struct AccumulateMaxVertexes
  {
    std::size_t operator()(std::size_t vertexes, const Polygon & poly);
  };
  void accMaxVertexes(const std::vector<Polygon> & polygons, std::ostream & out);

  //MAX полностью
  void max(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);

  //[MIN <AREA>]
  struct AccumulateMinArea
  {
    double operator()(double area, const Polygon & poly);
  };
  void accMinArea(const std::vector<Polygon> & polygons, std::ostream & out);

  //[MIN <VERTEXES>]
  struct AccumulateMinVertexes
  {
    size_t operator()(size_t vertexes, const Polygon & poly);
  };
  void accMinVertexes(const std::vector<Polygon> & polygons, std::ostream & out);

  //MIN полностью
  void min(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);

  //[COUNT <EVEN|ODD>]
  struct AccumulateCountParity
  {
    size_t operator()(size_t count, const Polygon & poly, bool isEven);
  };
  void accCountParityEven(const std::vector<Polygon> & polygons, std::ostream & out);
  void accCountParityOdd(const std::vector<Polygon> & polygons, std::ostream & out);

  //[COUNT <num-of-vertex>]
  struct AccumulateCountNumOfVertex
  {
    std::size_t numOfVertex;
    std::size_t operator()(std::size_t count, const Polygon & poly);
  };
  void accCountNumOfVertex(const std::vector<Polygon> & polygons, std::ostream & out, std::size_t numOfVertex);

  //COUNT полностью
  void count(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);

  //[PERMS <Polygon>]
  bool isPerm(const Polygon & poly1, const Polygon & poly2);
  void perm(const std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);

  //[RMECHO <Polygon>]
  struct IdenticalPoly
  {
    Polygon poly;
    bool operator()(const Polygon & poly1, const Polygon & poly2);
  };
  void rmecho(std::vector<Polygon> & polygons, std::istream & in, std::ostream & out);
}

#endif
