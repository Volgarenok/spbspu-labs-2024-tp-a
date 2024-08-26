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
    void predArea(const std::vector< Polygon >& data, std::ostream& out, BinaryPred pred);
    template < class BinaryPred >
    void predVertexes(const std::vector< Polygon >& data, std::ostream& out, BinaryPred pred);
    bool isEven(size_t n);
    bool emptyFilter(const Polygon&);
    size_t parseNumOfVertexes(const std::string& argument);
  }

  namespace cmd
  {
    using Filter = std::function< bool(const Polygon&) >;
    using Calculator = std::function< double(const Polygon&) >;

    using AreaArgs = std::map< std::string, std::pair< Filter, Calculator > >;
    using CountArgs = std::map< std::string, Filter >;

    using MinMaxArgs = std::map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >;
  }

  void cmdArea(const std::vector< Polygon >& data, const cmd::AreaArgs& args, std::istream& in, std::ostream& out);
  void cmdMinMax(const std::vector< Polygon >& data, const cmd::MinMaxArgs& args, std::istream& in, std::ostream& out);
  void cmdCount(const std::vector< Polygon >& data, const cmd::CountArgs& args, std::istream& in, std::ostream& out);
  void cmdRmEcho(std::vector< Polygon >& data, std::istream& in, std::ostream& out);
  void cmdRightShapes(const std::vector< Polygon >& data, std::ostream& out);
}

template < class BinaryPred >
void kravchenko::predicates::predArea(const std::vector< Polygon >& data, std::ostream& out, BinaryPred pred)
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

template < class BinaryPred >
void kravchenko::predicates::predVertexes(const std::vector< Polygon >& data, std::ostream& out, BinaryPred pred)
{
  using namespace std::placeholders;
  out << getNumberOfVertexes(*std::min_element(data.cbegin(), data.cend(), std::bind(
    pred,
    std::bind(getNumberOfVertexes, _1),
    std::bind(getNumberOfVertexes, _2)
  )));
}


#endif
