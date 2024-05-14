#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Polygon.hpp"
#include "PolygonManager.hpp"

namespace kozakova
{
  using namespace std::placeholders;

  void areaCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    if (s == "EVEN")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonsAreaEven{}, _1, _2)) << "\n";
    }
    else if (s == "ODD")
    {
      out << std::fixed << std::setprecision(1) << std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(kozakova::PolygonsAreaOdd{}, _1, _2)) << "\n";
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

  void maxCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
        out << std::fixed << std::setprecision(1) << getArea(*std::max_element(polygons.begin(), polygons.end(), minArea)) << "\n";
      }
      else if (s == "VERTEXES")
      {
        out << std::fixed << std::setprecision(1) << (*std::max_element(polygons.begin(), polygons.end(), minVertexes)).points.size() << "\n";
      }
      else
      {
        out << "<INVALID COMMAND>\n";
      }
    }
  }

  void minCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
        out << std::fixed << std::setprecision(1) << getArea(*std::min_element(polygons.begin(), polygons.end(), minArea)) << "\n";
      }
      else if (s == "VERTEXES")
      {
        out << std::fixed << std::setprecision(1) << (*std::min_element(polygons.begin(), polygons.end(), minVertexes)).points.size() << "\n";
      }
      else
      {
        out << "<INVALID COMMAND>\n";
      }
    }
  }

  void countCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    if (s == "EVEN")
    {
      out << std::count_if(polygons.begin(), polygons.end(), isEvenCountVertexes) << "\n";
    }
    else if (s == "ODD")
    {
      out << std::count_if(polygons.begin(), polygons.end(),isOddCountVertexes) << "\n";
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
        out << std::count_if(polygons.begin(), polygons.end(),
          std::bind(isNCountVertexes, _1, n)) << "\n";
      }
    }
    else
    {
      out << "<INVALID COMMAND>\n";
    }
  }

  void rectsCmd(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    out << std::count_if(polygons.begin(), polygons.end(), isRect) << "\n";
  }

  void maxseqCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    kozakova::Polygon data;
    in >> data;
    if (data.points.size() < 3)
    {
      out << "<INVALID COMMAND>\n";
    }
    else
    {
      PolygonMaxSeq seq{0,0};
      int isSeq = std::count_if(polygons.begin(), polygons.end(),
        std::bind(std::ref(seq), _1, data));
      if (!isSeq)
      {
        out << "<INVALID COMMAND>\n";
      }
      else
      {
        out << seq.maxseq << "\n";
      }
    }
  }
}
