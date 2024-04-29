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
  using namespace std::placeholders;

  void area(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    if (s == "EVEN")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonsArea{}, _1, _2, false)) << "\n";
    }
    else if (s == "ODD")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonsArea{}, _1, _2, true)) << "\n";
    }
    else if (s == "MEAN")
    {
      if (polygons.size() < 1)
      {
        out << "<INVALID COMMAND>\n";
      }
      else
      {
        out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
          kozakova::PolygonsArea{}) / polygons.size() << "\n";
      }
    }
    else if (s == std::to_string(std::stoi(s)))
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonsArea{}, _1, _2, static_cast< size_t >(std::stoi(s)))) << "\n";
    }
    else
    {
      out << "<INVALID COMMAND>\n";
    }
  }

  void max(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    if (polygons.size() < 1)
    {
      out << "<INVALID COMMAND>\n";
    }
    if (s == "AREA")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        kozakova::PolygonMaxArea{}) << "\n";
    }
    else if (s == "VERTEXES")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0,
        kozakova::PolygonMaxVertexes{}) << "\n";
    }
    else
    {
      out << "<INVALID COMMAND>\n";
    }
  }

  void min(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    if (polygons.size() < 1)
    {
      out << "<INVALID COMMAND>\n";
    }
    if (s == "AREA")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 1000000.0,
        kozakova::PolygonMinArea{}) << "\n";
    }
    else if (s == "VERTEXES")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 1000000,
        kozakova::PolygonMinVertexes{}) << "\n";
    }
    else
    {
      out << "<INVALID COMMAND>\n";
    }
  }

  void count(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    if (s == "EVEN")
    {
      out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonCount{}, _1, _2, false)) << "\n";
    }
    else if (s == "ODD")
    {
      out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonCount{}, _1, _2, true)) << "\n";
    }
    else if (s == std::to_string(std::stoi(s)))
    {
      out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonCount{}, _1, _2, static_cast< size_t >(std::stoi(s)))) << "\n";
    }
    else
    {
      out << "<INVALID COMMAND>\n";
    }
  }

  void rects(const std::vector< kozakova::Polygon >& polygons, std::ostream& out)
  {
    out << std::accumulate(polygons.begin(), polygons.end(), 0, kozakova::PolygonRect{}) << "\n";
  }

  void maxseq(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    kozakova::Polygon data;
    in >> data;
    out << std::accumulate(polygons.begin(), polygons.end(), 0,
      std::bind(kozakova::PolygonMaxSeq{}, _1, _2, data)) << "\n";
  }
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
        catch (const std::overflow_error& e)
        {
          std::cerr << "<ERROR: " << e.what() << ">\n";
        }
        catch (const std::out_of_range&)
        {
          std::cerr << "<INVALID COMMAND>\n";
          std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
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
