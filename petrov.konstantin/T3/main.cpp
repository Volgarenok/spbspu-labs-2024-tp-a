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
  using typeDouVecPol = std::function< double(const std::vector< Polygon >&) >;
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
  using typeDouVecPolSizet = std::function< double(const std::vector< Polygon >&, size_t) >;
  std::map< std::string, typeDouVecPolSizet > cmdWithNumArgs;
  {
    using namespace std::placeholders;
    cmdWithNumArgs["AREA"] = getAreaNumOfVertexes;
    cmdWithNumArgs["COUNT"] = countPolygonsNumOfVertexes;
  }
  using typeDouVecPolPol = std::function< double(const std::vector< Polygon >&, const Polygon&) >;
  std::map< std::string, typeDouVecPolPol > cmdWithPolArgs;
  {
    using namespace std::placeholders;
    cmdWithPolArgs["SAME"] = std::bind(&countSame, polygons, _2);
  }
  //Какие то беды с плейсхолдером
  std::string cmd = "";
  std::cout << '\n';
  while (in >> cmd)
  {
    if (cmdWithPolArgs.find(cmd) != cmdWithPolArgs.cend())
    {
      try
      {
        Polygon arg;
        in >> arg;
        out << cmdWithPolArgs.at(cmd)(polygons, arg) << '\n';
      }
      catch (const std::out_of_range&)
      {
      }
    }
    try
    {
      std::string arg;
      in >> arg;
      out << cmdWithNumArgs.at(cmd + ' ' + arg)(cmd, arg);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
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
