#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <limits>
#include "Polygon.hpp"
#include "PolygonManager.hpp"

namespace kozakova
{
  void area(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out);

  void max(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out);

  void min(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out);

  void count(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out);

  void rects(const std::vector< kozakova::Polygon >& polygons, std::ostream& out);

  void maxseq(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out);
}


int main(int argc, char* argv[])
{
  if (argc > 1)
  {
    std::string fname = argv[1];
    std::ifstream file(fname);

    if (file.is_open())
    {
      std::vector< kozakova::Polygon > polygons;
      using inputIt = std::istream_iterator< kozakova::Polygon >;
      while (!file.eof())
      {
        std::copy(inputIt{ file }, inputIt{}, std::back_inserter(polygons));
        file.clear();
        file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
      std::map < std::string, std::function< void(std::istream&, std::ostream&) > > commands;
      {
        using namespace std::placeholders;
        commands["AREA"] = std::bind(kozakova::area, std::cref(polygons), _1, _2);
        commands["MAX"] = std::bind(kozakova::max, std::cref(polygons), _1, _2);
        commands["MIN"] = std::bind(kozakova::min, std::cref(polygons), _1, _2);
        commands["COUNT"] = std::bind(kozakova::count, std::cref(polygons), _1, _2);
        commands["RECTS"] = std::bind(kozakova::rects, std::cref(polygons), _2);
        commands["MAXSEQ"] = std::bind(kozakova::maxseq, std::cref(polygons), _1, _2);
      }

      std::string cmd;
      while (std::cin >> cmd)
      {
        try
        {
          commands.at(cmd)(std::cin, std::cout);
        }
        catch (const std::out_of_range&)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        catch (...)
        {
          std::cout << "<INVALID COMMAND>\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    else
    {
      return 2;
    }
    file.close();
  }
  else
  {
    std::cerr << "not file" << "\n";
    return 1;
  }
  return 0;
}
