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
void petrov::run(std::istream& in, std::ostream& out, std::vector< Polygon >& polygons)
{
  std::map< std::string, std::function<double(std::vector< Polygon >&) > > cmdDictionary;
  {
    using namespace std::placeholders;
    cmdDictionary["AREA EVEN"] = std::bind(&getAreaEO, _1, true);
    cmdDictionary["AREA ODD"] = std::bind(&getAreaEO, _1, false);
    cmdDictionary["AREA MEAN"] = getAreaAverage;
    cmdDictionary["AREA"] = std::bind(&getAreaNOV, _1, in);
    cmdDictionary["MAX AREA"] = std::bind(&getExtremum, _1, true, true);
    cmdDictionary["MAX VERTEXES"] = std::bind(&getExtremum, _1, false, true);
    cmdDictionary["MIN AREA"] = std::bind(&getExtremum, _1, true, false);
    cmdDictionary["MIN VERTEXES"] = std::bind(&getExtremum, _1, false, false);
    cmdDictionary["COUNT EVEN"] = std::bind(&countPolygonsEO, _1, true);
    cmdDictionary["COUNT ODD"] = std::bind(&countPolygonsEO, _1, false);
    cmdDictionary["COUNT"] = std::bind(&countNOV, _1, in);
  }
  std::string cmd = "";
  std::string arg = "";
  while (in >> cmd >> arg)
  {
    try
    {
      cmdDictionary.at(cmd + ' ' + arg)(polygons);
    }
    catch (const std::out_of_range&)
    {
      cmdDictionary.at(cmd)(polygons);
    }
    catch (...)
    {
      out << "<INVALID COMMAND>\n";
    }
    cmd = "";
    arg = "";
  }
}
double petrov::getAreaNOV(std::vector< Polygon >& polygons, std::istream& in)
{
  size_t nOV = 0;
  in >> nOV;
  if (in && nOV > 0)
  {
    return getAreaNumOfVertexes(polygons, nOV);
  }
  else
  {
    throw;
  }
}
double petrov::countNOV(std::vector< Polygon >& polygons, std::istream& in)
{
  size_t nOV = 0;
  in >> nOV;
  if (in && nOV > 0)
  {
    return countPolygonsNumOfVertexes(polygons, nOV);
  }
  else
  {
    throw;
  }
}
