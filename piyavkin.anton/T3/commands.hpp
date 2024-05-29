#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iomanip>
#include <functional>
#include "polygon.hpp"
#include "streamguard.hpp"

namespace piyavkin
{
  void cmdArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  void cmdMin(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  void cmdMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  void cmdCount(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  void cmdLessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  void cmdIntersections(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  namespace detail
  {
    template< class F >
    void getAreaMinMax(std::ostream& out, const std::vector< Polygon >& pols, F f)
    {
      std::vector< double > areas(pols.size(), 0);
      std::transform(pols.begin(), pols.end(), areas.begin(), getAreaPol);
      StreamGuard guard(out);
      out << std::setprecision(1) << std::fixed << *std::min_element(areas.begin(), areas.end(), f);
    }
    size_t getVertex(const Polygon& pol);
    template< class F >
    void getVertexMinMax(std::ostream& out, const std::vector< Polygon >& pols, F f)
    {
      std::vector< size_t > areas(pols.size(), 0);
      std::transform(pols.begin(), pols.end(), areas.begin(), getVertex);
      out << *std::min_element(areas.begin(), areas.end(), f);
    }
  }
}
#endif
