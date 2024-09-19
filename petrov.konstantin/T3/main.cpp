#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <functional>
#include <map>
#include <string>
#include <iomanip>
#include "Geometry.hpp"
#include "Commands.hpp"
#include "IOWork.hpp"

void run(std::vector< petrov::Polygon >& polygons, std::istream& in, std::ostream& out)
{
  using namespace petrov;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmdDictionary;
  {
    using namespace std::placeholders;
    cmdDictionary["AREA"] = std::bind(&cmdArea, polygons, _1, _2);
    cmdDictionary["MAX"] = std::bind(&cmdMax, polygons, _1, _2);
    cmdDictionary["MIN"] = std::bind(&cmdMin, polygons, _1, _2);
    cmdDictionary["COUNT"] = std::bind(&cmdCount, polygons, _1, _2);
    cmdDictionary["RMECHO"] = std::bind(&cmdRmEcho, polygons, _1, _2);
    cmdDictionary["SAME"] = std::bind(&cmdSame, polygons, _1, _2);
  }
  std::string cmd = "";
  while (in >> cmd)
  {
    try
    {
      cmdDictionary.at(cmd)(in, out);
    }
    catch (...)
    {
      out << "<INVALID COMMAND>\n";
      in.clear();
      using numLim = std::numeric_limits< std::streamsize >;
      in.ignore(numLim::max(), '\n');
    }
  }
}

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "<INVALID ARGUMENTS>\n";
    return 1;
  }

  std::ifstream fin(argv[1], std::ios::in);
  std::vector< petrov::Polygon > polygons;
  petrov::readFromStream(fin, polygons);
  fin.close();

  std::cout << std::fixed << std::setprecision(1);
  run(polygons, std::cin, std::cout);

  return 0;
}
