#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <map>
#include "Polygon.hpp"

namespace kozakova
{
  using namespace std::placeholders;

  template< class UnaryPredicate >
  double getSumArea(const std::vector< Polygon >& polygons, UnaryPredicate P);
  double doAreaEven(const std::vector< Polygon >& polygons);
  double doAreaOdd(const std::vector< Polygon >& polygons);
  double doAreaMean(const std::vector< Polygon >& polygons);
  double doAreaNum(const std::vector< Polygon >& polygons, size_t n);

  void doAreaCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::string s;
    in >> s;
    double result = 0.0;
    std::map< std::string, std::function< double() > > subcommand;
    {
      using namespace std::placeholders;
      subcommand["EVEN"] = std::bind(doAreaEven, polygons);
      subcommand["ODD"] = std::bind(doAreaOdd, polygons);
      subcommand["MEAN"] = std::bind(doAreaMean, polygons);
    }
    try
    {
      size_t n = std::stoull(s);
      if (n < 3)
      {
        throw std::logic_error("FEW VERTEXES");
      }
      result = doAreaNum(polygons, n);
    }
    catch (const std::invalid_argument&)
    {
      result = subcommand[s]();
    }
    std::vector< double > areas;
    out << std::fixed << std::setprecision(1) << result << "\n";
  }

  void doMinMaxCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, const std::string& name)
  {
    std::string s;
    in >> s;
    if (polygons.empty())
    {
      throw std::logic_error("NO POLYGONS");
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
        out << std::fixed << std::setprecision(1) << (*std::max_element(polygons.begin(), polygons.end(), minVertexes)).points.size() << "\n";
      }
      else
      {
        out << std::fixed << std::setprecision(1) << (*std::min_element(polygons.begin(), polygons.end(), minVertexes)).points.size() << "\n";
      }
    }
    else
    {
      throw std::logic_error("INVALID COMMAND");
    }
  }

  void doMaxCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    doMinMaxCommand(polygons, in, out, "max");
  }

  void doMinCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    doMinMaxCommand(polygons, in, out, "min");
  }

  void doCountCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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
      size_t n = static_cast< size_t >(std::stoi(s));
      if (n < 3)
      {
        throw std::logic_error("FEW VERTEXES");
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

  void doRectsCommand(const std::vector< Polygon >& polygons, std::ostream& out)
  {
    out << std::count_if(polygons.begin(), polygons.end(), isRect) << "\n";
  }

  struct PolygonMaxSeq
  {
    size_t cur;
    size_t maxseq;
    bool operator()(const Polygon& polygon, const Polygon& data);
  };

  void doMaxseqCommand(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
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

  bool PolygonMaxSeq::operator()(const Polygon& polygon, const Polygon& data)
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

  template< class UnaryPredicate >
  double getSumArea(const std::vector< Polygon >& polygons, UnaryPredicate P)
  {
    std::vector< Polygon > rightPolygons;
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(rightPolygons), P);
    std::vector< double > areas;
    std::transform(rightPolygons.cbegin(), rightPolygons.cend(), std::back_inserter(areas), getArea);
    double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    return result;
  }

  double doAreaEven(const std::vector< Polygon >& polygons)
  {
    return getSumArea(polygons, isEvenCountVertexes);
  }

  double doAreaOdd(const std::vector< Polygon >& polygons)
  {
    return getSumArea(polygons, isOddCountVertexes);
  }

  double doAreaMean(const std::vector< Polygon >& polygons)
  {
    if (polygons.empty())
    {
      throw std::logic_error("NO POLYGONS FOR AREA MEAN COMMAND");
    }
    std::vector< double > areas;
    std::transform(polygons.cbegin(), polygons.cend(), std::back_inserter(areas), getArea);
    double result = std::accumulate(areas.cbegin(), areas.cend(), 0.0);
    result /= polygons.size();
    return result;
  }

  double doAreaNum(const std::vector< Polygon >& polygons, size_t n)
  {
    return getSumArea(polygons, std::bind(isNCountVertexes, _1, n));
  }
}
