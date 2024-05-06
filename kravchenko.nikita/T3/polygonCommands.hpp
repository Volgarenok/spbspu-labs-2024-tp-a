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
  namespace detail
  {
    bool isEvenNumberOfVertexes(const Polygon& p);
    std::size_t getNumberOfVertexes(const Polygon& p);
    double accumulateAreaParity(double acc, const Polygon& p, bool isEven);
    double accumulateAreaNumOfVertex(double acc, const Polygon& p, std::size_t numOfVertexes);
  }

  void cmdArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);

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
      lessArea = std::bind(
        std::less< double >{},
        std::bind(&Polygon::getArea, _1),
        std::bind(&Polygon::getArea, _2)
      );

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
      std::function< bool(const Polygon&, const Polygon&) > lessVertexes = std::bind(
        std::less< std::size_t >{},
        std::bind(detail::getNumberOfVertexes, _1),
        std::bind(detail::getNumberOfVertexes, _2)
      );

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
