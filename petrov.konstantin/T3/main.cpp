#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <limits>
#include <functional>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>
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
  using typeDou = std::function< double() >;
  std::map< std::string, typeDou > cmdDoubleNoArgs;
  cmdDoubleNoArgs["AREA EVEN"] = std::bind(&getAreaEO, polygons, true);
  cmdDoubleNoArgs["AREA ODD"] = std::bind(&getAreaEO, polygons, false);
  cmdDoubleNoArgs["AREA MEAN"] = std::bind(&getAreaAverage, polygons);
  cmdDoubleNoArgs["MAX AREA"] = std::bind(&getExtremum, polygons, true, true);
  cmdDoubleNoArgs["MIN AREA"] = std::bind(&getExtremum, polygons, true, false);

  std::map< std::string, typeDou > cmdIntNoArgs;
  {
    cmdIntNoArgs["MAX VERTEXES"] = std::bind(&getExtremum, polygons, false, true);
    cmdIntNoArgs["MIN VERTEXES"] = std::bind(&getExtremum, polygons, false, false);
    cmdIntNoArgs["COUNT EVEN"] = std::bind(&countPolygonsEO, polygons, true);
    cmdIntNoArgs["COUNT ODD"] = std::bind(&countPolygonsEO, polygons, false);
  }

  using typeDouSizet = std::function< double(size_t) >;
  std::map< std::string, typeDouSizet > cmdDoubleWithNumArgs;
  {
    using namespace std::placeholders;
    cmdDoubleWithNumArgs["AREA"] = std::bind(&getAreaNumOfVertexes, polygons, _1);
  }

  std::map< std::string, typeDouSizet > cmdIntWithNumArgs;
  {
    using namespace std::placeholders;
    cmdIntWithNumArgs["COUNT"] = std::bind(&countPolygonsNumOfVertexes, polygons, _1);
  }

  using typeDouPol = std::function< double(const Polygon&) >;
  std::map< std::string, typeDouPol > cmdIntWithPolArgs;
  {
    using namespace std::placeholders;
    cmdIntWithPolArgs["SAME"] = std::bind(&countSame, polygons, _1);
    cmdIntWithPolArgs["RMECHO"] = std::bind(&rmEcho, polygons, _1);
  }

  std::string cmd = "";
  while (in >> cmd)
  {
    try
    {
      if (cmdIntWithPolArgs.find(cmd) != cmdIntWithPolArgs.cend())
      {
        try
        {
          Polygon arg;
          in >> arg;
          if (arg.points.size() < 3)
          {
            throw std::logic_error("INVALID MASK");
          }
          out << static_cast< int >(cmdIntWithPolArgs.at(cmd)(arg)) << '\n';
          continue;
        }
        catch (const std::out_of_range&)
        {
        }
      }

      std::string arg;
      in >> arg;
      if (std::find_if_not(arg.cbegin(), arg.cend(), myIsdigit) == arg.cend())
      {
        try
        {
          out << cmdDoubleWithNumArgs.at(cmd)(static_cast< std::size_t >(std::stoi(arg))) << '\n';
          continue;
        }
        catch (const std::out_of_range&)
        {
        }
        out << static_cast< int >(cmdIntWithNumArgs.at(cmd)(static_cast< std::size_t >(std::stoi(arg)))) << '\n';
        continue;
      }
      else
      {
        try
        {
          out << cmdDoubleNoArgs.at(cmd + ' ' + arg)() << '\n';
          continue;
        }
        catch (const std::out_of_range&)
        {
        }
        out << static_cast< int >(cmdIntNoArgs.at(cmd + ' ' + arg)()) << '\n';
        continue;
      }
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

  using petrov::Polygon;
  std::ifstream fin(argv[1], std::ios::in);
  std::vector< Polygon > polygons;
  readFromFile(fin, polygons);
  fin.close();

  auto cIt = std::ostream_iterator< Polygon >(std::cout, "\n");
  std::copy(polygons.cbegin(), polygons.cend(), cIt);

  std::cout << std::fixed << std::setprecision(1);
  run(std::cin, std::cout, polygons);

  return 0;
}
