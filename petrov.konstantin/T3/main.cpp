#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <limits>
#include <functional>
#include <map>
#include <string>
#include "Geometry.hpp"
#include "Commands.hpp"
#include "Delimiter.h"

template <class T>
std::vector< T >& readFromFile(std::istream& fin, std::vector< T >& dest)
{
  while (!fin.eof())
  {
    std::istream_iterator< T > finItFirst(fin);
    std::istream_iterator< T > finItLast;
    std::copy(finItFirst, finItLast, std::back_inserter(dest));
    if (fin.fail())
    {
      fin.clear();
      using numLim = std::numeric_limits< std::streamsize >;
      fin.ignore(numLim::max(), '\n');
    }
  }
  return dest;
}
void run(std::istream& in, std::ostream& out, std::vector< petrov::Polygon >& polygons)
{
  using namespace petrov;
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
  }
  std::map< std::string, std::function< double(const std::vector< Polygon >&, size_t) > > cmdWithNumArgs;
  {
    using namespace std::placeholders;
    cmdWithNumArgs["AREA"] = getAreaNumOfVertexes;
    cmdWithNumArgs["COUNT"] = countPolygonsNumOfVertexes;
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

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    std::cout << "No arguments provided\n";
    return 0;
  }

  using petrov::Polygon;
  std::ifstream fin(argv[1], std::ios::in);
  std::vector< Polygon > polygons;
  readFromFile(fin, polygons);
  fin.close();

  std::ostream_iterator< Polygon > coutIt(std::cout, "\n");
  std::copy(polygons.begin(), polygons.end(), coutIt);

  std::cout << '\n';
  run(std::cin, std::cout, polygons);

  return 0;
}
