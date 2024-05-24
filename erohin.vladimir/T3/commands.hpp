#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <iosfwd>
#include "polygon.hpp"

namespace erohin
{

  void doAreaCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doMaxCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doMinCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doCountCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doInFrameCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  void doRightShapesCommand(const std::vector< Polygon > & context, std::istream & input, std::ostream & output);
  namespace detail
  {
    template< class UnaryPredicate >
    double getSumAreaIf(const std::vector< Polygon > & context, UnaryPredicate P)
    {
      std::vector< Polygon > selected;
      std::copy_if(context.cbegin(), context.cend(), std::back_inserter(selected), P);
      return getArea(selected);
    }
  }
}

#endif
