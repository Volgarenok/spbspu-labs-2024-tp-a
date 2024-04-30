#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
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
      size_t n = static_cast<size_t>(std::stoi(s));
      if (n < 3)
      {
        out << "<INVALID COMMAND>\n";
      }
      else
      {
        out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
          std::bind(kozakova::PolygonsArea{}, _1, _2, n)) << "\n";
      }
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
    else
    {
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
  }

  void min(const std::vector< kozakova::Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    if (polygons.size() < 1)
    {
      out << "<INVALID COMMAND>\n";
    }
    else
    {
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
      size_t n = static_cast<size_t>(std::stoi(s));
      if (n < 3)
      {
        out << "<INVALID COMMAND>\n";
      }
      else
      {
        out << std::accumulate(polygons.begin(), polygons.end(), 0.0,
          std::bind(kozakova::PolygonCount{}, _1, _2, n)) << "\n";
      }
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
    if (data.points.size() < 3)
    {
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      int m = std::accumulate(polygons.begin(), polygons.end(), 0,
        std::bind(kozakova::PolygonMaxSeq{}, _1, _2, data));
      if (m == 0)
      {
        out << "<INVALID COMMAND>\n";
      }
      else
      {
        out << m << "\n";
      }
    }
  }
}
