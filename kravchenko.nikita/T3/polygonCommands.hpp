#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP

#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <streamGuard.hpp>
#include "polygon.hpp"

namespace kravchenko
{
  template < class BinaryPred >
  void predicateElement(const std::vector< Polygon >& data, std::istream& in, std::ostream& out, BinaryPred pred);

  bool isEven(size_t n);
  size_t parseNumberOfVertexes(const std::string& argument);

  void cmdArea(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdMin(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdCount(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdRmEcho(std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdRightShapes(const std::vector< Polygon >& data, std::ostream& out);

  template < class BinaryPred >
  void predicateElement(const std::vector< Polygon >& data, std::istream& in, std::ostream& out, BinaryPred pred)
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
      StreamGuard guard(out);
      out << std::setprecision(1) << std::fixed;
      out << getArea(*std::min_element(data.cbegin(), data.cend(), std::bind(
        pred,
        std::bind(getArea, _1),
        std::bind(getArea, _2)
      )));
    }
    else if (argument == "VERTEXES")
    {
      using namespace std::placeholders;
      out << getNumberOfVertexes(*std::min_element(data.cbegin(), data.cend(),
        std::bind(pred, std::bind(getNumberOfVertexes, _1), std::bind(getNumberOfVertexes, _2)))
      );
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
}

#endif
