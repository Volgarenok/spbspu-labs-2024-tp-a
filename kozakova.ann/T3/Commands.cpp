#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "Polygon.hpp"

namespace kozakova
{
  using namespace std::placeholders;

  struct PolygonMaxSeq
  {
    size_t cur;
    size_t maxseq;
    bool operator()(const Polygon& polygon, const Polygon& data)
    {
      if (polygon == data)
      {
        cur++;
        maxseq = std::max(maxseq, cur);
      }
      else
      {
        cur = 0;
      }
      return maxseq;
    }
  };

  void areaCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    std::vector< Polygon > rightPolygons;
    if (s == "EVEN")
    {
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(rightPolygons), isEvenCountVertexes);
    }
    else if (s == "ODD")
    {
      std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(rightPolygons), isOddCountVertexes);
    }
    else if (s == "MEAN")
    {
      if (polygons.empty())
      {
        throw std::logic_error("INVALID COMMAND");
      }
      else
      {
        rightPolygons = polygons;
      }
    }
    else if (s == std::to_string(std::stoi(s)))
    {
      size_t n = static_cast<size_t>(std::stoi(s));
      if (n < 3)
      {
        throw std::logic_error("INVALID COMMAND");
      }
      else
      {
        std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(rightPolygons), std::bind(isNCountVertexes,_1,n));
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
    std::vector< double > areas;
    std::transform(rightPolygons.cbegin(), rightPolygons.cend(), std::back_inserter(areas), getArea);
    double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    if (s == "MEAN")
    {
      result /= rightPolygons.size();
    }
    out << std::fixed << std::setprecision(1) << result << "\n";
  }

  void minMaxCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, const std::string& name)
  {
    std::string s;
    in >> s;
    if (polygons.empty())
    {
      throw std::logic_error("INVALID COMMAND");
    }
    if (s == "AREA")
    {
      if (name == "max")
      {
        out << std::fixed << std::setprecision(1) << getArea(*std::max_element(polygons.begin(), polygons.end(), minArea)) << "\n";
      }
      else
      {
        out << std::fixed << std::setprecision(1) << getArea(*std::min_element(polygons.begin(), polygons.end(), minArea)) << "\n";
      }
    }
    else if (s == "VERTEXES")
    {
      if (name == "max")
      {
        out << std::fixed << std::setprecision(1) << (*std::max_element(polygons.begin(), polygons.end(),
          minVertexes)).points.size() << "\n";
      }
      else
      {
        out << std::fixed << std::setprecision(1) << (*std::min_element(polygons.begin(), polygons.end(),
          minVertexes)).points.size() << "\n";
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void maxCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    minMaxCmd(polygons, in, out, "max");
  }

  void minCmd(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    minMaxCmd(polygons, in, out, "min");
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
        throw std::logic_error("INVALID COMMAND");
      }
      else
      {
        out << std::count_if(polygons.begin(), polygons.end(), std::bind(isNCountVertexes, _1, n)) << "\n";
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
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
      throw std::logic_error("INVALID COMMAND");
    }
    else
    {
      PolygonMaxSeq seq{0,0};
      size_t numberSeq = std::count_if(polygons.begin(), polygons.end(), std::bind(std::ref(seq), _1, data));
      if (numberSeq < 1)
      {
        throw std::logic_error("INVALID COMMAND");
      }
      else
      {
        out << seq.maxseq << "\n";
      }
    }
  }
}
