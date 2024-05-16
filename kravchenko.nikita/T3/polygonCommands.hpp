#ifndef POLYGON_COMMANDS_HPP
#define POLYGON_COMMANDS_HPP

#include <algorithm>
#include <exception>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <streamGuard.hpp>
#include "polygon.hpp"

namespace kravchenko
{
  namespace predicates
  {
    template < class BinaryPred >
    void predElement(const std::vector< Polygon >& data, std::istream& in, std::ostream& out, BinaryPred pred);
    bool isEven(size_t n);
    bool noFilter(const Polygon&);
    size_t parseNumOfVertexes(const std::string& argument);
  }

  namespace cmd
  {
    using Filter = std::function< bool(const Polygon&) >;
    using Calculator = std::function< double(const Polygon&) >;

    using AreaArgs = std::map< std::string, std::pair< Filter, Calculator > >;
    using CountArgs = std::map< std::string, Filter >;

    struct DataTracker
    {
      const std::vector< Polygon >& data;
      size_t getSize() const;
    };
  }

  void cmdArea(const std::vector< Polygon >& data, const cmd::AreaArgs& args, std::istream& in, std::ostream& out);
  void cmdMin(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdMax(const std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdCount(const std::vector< Polygon >& data, const cmd::CountArgs& args, std::istream& in, std::ostream& out);
  void cmdRmEcho(std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdRightShapes(const std::vector< Polygon >& data, std::ostream& out);

  template < class BinaryPred >
  void predicates::predElement(const std::vector< Polygon >& data, std::istream& in, std::ostream& out, BinaryPred pred)
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
      out << getNumberOfVertexes(*std::min_element(data.cbegin(), data.cend(), std::bind(
        pred,
        std::bind(getNumberOfVertexes, _1),
        std::bind(getNumberOfVertexes, _2)
      )));
    }
    else
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
}

#endif
