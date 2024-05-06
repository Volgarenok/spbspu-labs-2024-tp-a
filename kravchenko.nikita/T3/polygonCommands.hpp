#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP

#include <exception>
#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <string>
#include <streamGuard.hpp>
#include "polygon.hpp"

namespace kravchenko
{
  void cmdArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  namespace area
  {
    struct AccumulateAreaParity
    {
      double operator()(double acc, const Polygon& p, bool isEven);
    };
    struct AccumulateAreaMean
    {
      std::size_t numOfPolygons;
      double operator()(double acc, const Polygon& p);
    };
    struct AccumulateAreaNumOfVertex
    {
      std::size_t numOfVertexes;
      double operator()(double acc, const Polygon& p);
    };
  }

  template< bool isMin >
  void cmdMinMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);

  void cmdCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);

  void cmdRmEcho(std::vector< Polygon >& data, std::istream& in, std::ostream& out);

  void cmdRightShapes(const std::vector< Polygon >& data, std::ostream& out);

  template < bool isMin >
  void cmdMinMax(const std::vector<Polygon> &data, std::istream &in, std::ostream &out)
  {
    if (data.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    std::string argument;
    in >> argument;
    if (argument == "AREA")
    {
      using namespace std::placeholders;
      std::function< bool(const Polygon&, const Polygon&) > lessArea;
      lessArea = std::bind(std::less< double >{}, std::bind(&Polygon::getArea, _1), std::bind(&Polygon::getArea, _2));

      StreamGuard guard(out);
      out << std::setprecision(1) << std::fixed;
      if (isMin)
      {
        out << (*std::min_element(data.cbegin(), data.cend(), lessArea)).getArea();
      }
      else
      {
        out << (*std::max_element(data.cbegin(), data.cend(), lessArea)).getArea();
      }
    }
    else if (argument == "VERTEXES")
    {
      using namespace std::placeholders;
      std::function< std::size_t(const Polygon&) > getPointsCount = std::bind(&std::vector< Point >::size, std::bind(&Polygon::points, _1));
      std::function< bool(const Polygon&, const Polygon&) > lessVertexes;
      lessVertexes = std::bind(std::less< std::size_t >{}, std::bind(getPointsCount, _1), std::bind(getPointsCount, _2));

      if (isMin)
      {
        out << (*std::min_element(data.cbegin(), data.cend(), lessVertexes)).points.size();
      }
      else
      {
        out << (*std::max_element(data.cbegin(), data.cend(), lessVertexes)).points.size();
      }
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
}

#endif
