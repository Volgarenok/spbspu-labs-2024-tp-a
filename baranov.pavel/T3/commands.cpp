#include "commands.hpp"
#include <map>
#include <string>
#include <functional>

void baranov::area(std::vector< Polygon > & shapes, std::istream & in, std::ostream &)
{
  std::map< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds["EVEN"] = std::bind(areaEven, std::ref(shapes), _1, _2);
    cmds["ODD"] = std::bind(areaOdd, std::ref(shapes), _1, _2);
    cmds["MEAN"] = std::bind(areaMean, std::ref(shapes), _1, _2);
  }
}

void baranov::areaEven(std::vector< Polygon > & shapes, std::istream & in, std::ostream &out)
{}

void baranov::areaOdd(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{}

void baranov::areaMean(std::vector< Polygon > & shapes, std::istream & in, std::ostream & out)
{}
