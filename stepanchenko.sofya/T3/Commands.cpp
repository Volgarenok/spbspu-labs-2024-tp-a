#include "Commands.hpp"

#include <map>
#include <functional>
#include <algorithm>
#include <iomanip>

#include "Polygon.hpp"

void stepanchenko::areaCmd(const std::vector< Polygon > & polygons, std::istream& in, std::ostream& out)
{
  std::map< std::string, std::function< double() > > cmdArea;
  {
    using namespace std::placeholders;
    cmdArea["EVEN"] = std::bind(areaEven, polygons);
    cmdArea["ODD"] = std::bind(areaOdd, polygons);
    cmdArea["MEAN"] = std::bind(areaMean, polygons);
  }
    std::string arg;
    in >> arg;
    if ((arg == "MEAN") && polygons.empty())
    {
      throw std::logic_error("No figures");
    }
    StreamGuard stream(out);
    out << std::fixed << std::setprecision(1);
    try
    {
      out << cmdArea.at(arg)() << '\n';
    }
    catch (const std::out_of_range&)
    {
      int num = std::stoull(arg);
      if (num < 3)
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }
      out << areaNum(polygons, num) << '\n';
    }
}

