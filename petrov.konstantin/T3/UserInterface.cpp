#include "UserInterface.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "Commands.hpp"
#include "Geometry.hpp"

//count eon should be writen there
//not in the Commands.xpp
double testFunc1(const std::vector< petrov::Polygon >& pol)
{
  std::cout << "NO ARGS " << pol[0];
  return 1;
}
double testFunc2(const std::vector< petrov::Polygon >& pol, size_t arg)
{
  std::cout << "ARG: " << arg << ' ' << pol[0];
  return 1;
}

void petrov::run(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
{
  std::map< std::string, std::function< double(const std::vector< Polygon >&) > > cmdNoArgs;
  {
    using namespace std::placeholders;
    cmdNoArgs["AREA EVEN"] = std::bind(&getAreaEO, _1, true);
    cmdNoArgs["AREA ODD"] = std::bind(&getAreaEO, _1, false);
    cmdNoArgs["AREA MEAN"] = getAreaAverage;
    cmdNoArgs["MAX AREA"] = std::bind(&getExtremum, _1, true, true);
    cmdNoArgs["MAX VERTEXES"] = std::bind(&getExtremum, _1, false, true);
    cmdNoArgs["MIN AREA"] = std::bind(&getExtremum, _1, true, false);
    cmdNoArgs["MIN VERTEXES"] = std::bind(&getExtremum, _1, false, false);
    cmdNoArgs["COUNT EVEN"] = std::bind(&countPolygonsEO, _1, true);
    cmdNoArgs["COUNT ODD"] = std::bind(&countPolygonsEO, _1, false);
    cmdNoArgs["TEST FUNC"] = testFunc1;
  }
  std::map< std::string, std::function< double(const std::vector< Polygon >&, size_t) > > cmdWithNumArgs;
  {
    using namespace std::placeholders;
    cmdWithNumArgs["AREA"] = getAreaNumOfVertexes;
    cmdWithNumArgs["COUNT"] = countPolygonsNumOfVertexes;
    cmdWithNumArgs["TEST"] = testFunc2;
  }

  std::string cmd = "";
  std::string arg = "";
  std::cout << '\n';
  while (in >> cmd >> arg)
  {
    try
    {
      out << cmdNoArgs.at(cmd + ' ' + arg)(polygons) << '\n';
      continue;
    }
    catch (const std::out_of_range&)
    {
    }

    try
    {
      out << cmdWithNumArgs.at(cmd)(polygons, std::stoi(arg)) << '\n';
    }
    catch (...)
    {
      out << "<INVALID COMMAND>\n";
    }
  }
}

