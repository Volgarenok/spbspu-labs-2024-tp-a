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
//   void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
//   void lessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
//   void intersections(std::istream& in, std::ostream& out, const std::vector< Polygon >& pol);
  namespace detail
  {
    template< class F >
    void getAreaMinMax(std::ostream& out, const std::vector< Polygon >& pols, F f)
    {
      std::vector< double > areas;
      areas.reserve(pols.size());
      std::transform(pols.begin(), pols.end(), std::back_inserter(areas), getAreaPol);
      StreamGuard guard(out);
      out << std::setprecision(1) << std::fixed << *std::min_element(areas.begin(), areas.end(), f);
    }
    size_t getVertex(const Polygon& pol);
    template< class F >
    void getVertexMinMax(std::ostream& out, const std::vector< Polygon >& pols, F f)
    {
      std::vector< size_t > areas;
      areas.reserve(pols.size());
      std::transform(pols.begin(), pols.end(), areas.begin(), getVertex);
      out << *std::min_element(areas.begin(), areas.end(), f);
    }
  }
}
#endif
