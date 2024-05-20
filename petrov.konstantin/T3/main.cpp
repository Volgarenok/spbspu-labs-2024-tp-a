#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <limits>
#include <functional>
#include <map>
#include <string>
#include <algorithm>
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
  using typeDouVecPol = std::function< double() >;
  std::map< std::string, typeDouVecPol > cmdNoArgs;
  {
    //using namespace std::placeholders;
    cmdNoArgs["AREA EVEN"] = std::bind(&getAreaEO, polygons, true);
    cmdNoArgs["AREA ODD"] = std::bind(&getAreaEO, polygons, false);
    cmdNoArgs["AREA MEAN"] = std::bind(&getAreaAverage, polygons);
    cmdNoArgs["MAX AREA"] = std::bind(&getExtremum, polygons, true, true);
    cmdNoArgs["MAX VERTEXES"] = std::bind(&getExtremum, polygons, false, true);
    cmdNoArgs["MIN AREA"] = std::bind(&getExtremum, polygons, true, false);
    cmdNoArgs["MIN VERTEXES"] = std::bind(&getExtremum, polygons, false, false);
    cmdNoArgs["COUNT EVEN"] = std::bind(&countPolygonsEO, polygons, true);
    cmdNoArgs["COUNT ODD"] = std::bind(&countPolygonsEO, polygons, false);
  }
  using typeDouVecPolSizet = std::function< double(size_t) >;
  std::map< std::string, typeDouVecPolSizet > cmdWithNumArgs;
  {
    using namespace std::placeholders;
    cmdWithNumArgs["AREA"] = std::bind(&getAreaNumOfVertexes, polygons, _1);
    cmdWithNumArgs["COUNT"] = std::bind(&countPolygonsNumOfVertexes, polygons, _1);
  }
  using typeDouVecPolPol = std::function< double(const Polygon&) >;
  std::map< std::string, typeDouVecPolPol > cmdWithPolArgs;
  {
    using namespace std::placeholders;
    cmdWithPolArgs["SAME"] = std::bind(&countSame, polygons, _1);
  }

  std::string cmd = "";
  while (in >> cmd)
  {
    if (cmdWithPolArgs.find(cmd) != cmdWithPolArgs.cend())
    {
      try
      {
        Polygon arg;
        in >> arg;
        out << cmdWithPolArgs.at(cmd)(arg) << '\n';
        continue;
      }
      catch (const std::out_of_range&)
      {
      }
    }
    try
    {
      std::string arg;
      in >> arg;
      if (std::find_if_not(arg.cbegin(), arg.cend(), myIsdigit) == arg.cend())
      {
        out << cmdWithNumArgs.at(cmd)(static_cast< std::size_t >(std::stoi(arg))) << '\n';
      }
      else
      {
        out << cmdNoArgs.at(cmd + ' ' + arg)() << '\n';
      }
      continue;
    }
    catch (const std::out_of_range&)
    {
      out << "<INVALID COMMAND>\n";
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

  using petrov::Polygon;
  std::ifstream fin(argv[1], std::ios::in);
  std::vector< Polygon > polygons;
  readFromFile(fin, polygons);
  fin.close();

  // std::ostream_iterator< Polygon > coutIt(std::cout, "\n");
  // std::copy(polygons.begin(), polygons.end(), coutIt);

  //std::cout << '\n';
  run(std::cin, std::cout, polygons);

  return 0;
}
