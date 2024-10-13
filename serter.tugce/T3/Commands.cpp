#include <cmath>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <unordered_map>

#include <FormatGuard.hpp>
#include "ReadIO.h"
#include "Commands.h"

namespace serter
{
  bool isSize(const Polygon& polygon, size_t points)
  {
    return polygon.points.size() == points;
  }

  bool isCurrVertexes(size_t vertexes, const Polygon& polygon)
  {
    return polygon.points.size() == vertexes;
  }

  bool isEven(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  double getArea(const Polygon& polygon)
  {
    double res = 0.0;
    for (size_t i = 0; i < polygon.points.size() - 1; ++i)
    {
      res += 0.5 * (polygon.points[i].x * polygon.points[i + 1].y - polygon.points[i + 1].x * polygon.points[i].y);;
    }
    res += 0.5 * (polygon.points.back().x * polygon.points.front().y - polygon.points.front().x * polygon.points.back().y);
    return std::abs(res);
  }

  bool compareSize(const Polygon& lhs, const Polygon& rhs)
  {
    return lhs.points.size() < rhs.points.size();
  }

  bool compareArea(const Polygon& lhs, const Polygon& rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  double calcAreaMean(size_t polygons, const Polygon& polygon)
  {
    return getArea(polygon) / polygons;
  }

  bool isLessByArea(const Polygon& lhs, const Polygon& rhs)
  {
    return getArea(lhs) < getArea(rhs);
  }

  bool isEqualPolygon(const Polygon& lhs, const Polygon& rhs, const Polygon& polygon)
  {
    return (rhs.points == lhs.points) && (rhs.points == polygon.points);
  }

  bool operator==(const Polygon& lhs, const Polygon& rhs)
  {
    return lhs.points == rhs.points;
  }

  using func_t = std::function< double(const Polygon&) >;
  void outputAreaCmd(const std::vector< Polygon >& polygonsToCount, func_t func, std::ostream& output)
  {
    std::vector< double > areas(polygonsToCount.size());
    std::transform(polygonsToCount.cbegin(), polygonsToCount.cend(), areas.begin(), func);
    FormatGuard guard(output);
    output << std::setprecision(1) << std::fixed;
    output << std::accumulate(areas.cbegin(), areas.cend(), 0.0) << '\n';
  }

  void areaEvenCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    std::vector< Polygon > polygonsToCount;
    std::function< double(const Polygon&) > func = getArea;
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), isEven);
    outputAreaCmd(polygonsToCount, func, output);
  }

  void areaOddCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    std::vector< Polygon > polygonsToCount;
    std::function< double(const Polygon&) > func = getArea;
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), isOdd);
    outputAreaCmd(polygonsToCount, func, output);
  }

  void areaMeanCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid arg");
    }
    std::vector< Polygon > polygonsToCount;
    std::copy(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount));
    using namespace std::placeholders;
    std::function< double(const Polygon&) > func = std::bind(calcAreaMean, polygons.size(), _1);
    outputAreaCmd(polygonsToCount, func, output);
  }

  void areaVertexesCmd(const std::vector< Polygon >& polygons, size_t vertexes, std::ostream& output)
  {
    if (vertexes < 3)
    {
      throw std::invalid_argument("Invalid arg");
    }
    std::vector< Polygon > polygonsToCount;
    std::function< double(const Polygon&) > func = getArea;
    auto vertexPred = std::bind(isCurrVertexes, vertexes, std::placeholders::_1);
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(polygonsToCount), vertexPred);
    outputAreaCmd(polygonsToCount, func, output);
  }

  void minAreaCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid arg");
    }
    FormatGuard guard(output);
    output << std::fixed << std::setprecision(1);
    output << getArea(*(std::min_element(polygons.begin(), polygons.end(), compareArea))) << '\n';
  }

  void minVertexesCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid arg");
    }
    output << std::min_element(polygons.begin(), polygons.end(), compareSize)->points.size() << '\n';
  }

  void maxAreaCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid arg");
    }
    FormatGuard guard(output);
    output << std::fixed << std::setprecision(1);
    output << getArea(*(std::max_element(polygons.begin(), polygons.end(), compareArea))) << '\n';
  }

  void maxVertexesCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    if (polygons.empty())
    {
      throw std::invalid_argument("Invalid arg");
    }
    output << std::max_element(polygons.begin(), polygons.end(), compareSize)->points.size() << '\n';
  }

  void countOddCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    output << std::count_if(polygons.cbegin(), polygons.cend(), isOdd) << '\n';
  }

  void countEvenCmd(const std::vector< Polygon >& polygons, std::ostream& output)
  {
    output << std::count_if(polygons.cbegin(), polygons.cend(), isEven) << '\n';
  }

  void countVertexesCmd(const std::vector< Polygon >& polygons, size_t vertexes, std::ostream& output)
  {
    if (vertexes < 3)
    {
      throw std::invalid_argument("Invalid arg");
    }
    std::function< bool(const Polygon&) > pred = std::bind(isSize, std::placeholders::_1, vertexes);
    output << std::count_if(polygons.cbegin(), polygons.cend(), pred) << '\n';
  }
}

void serter::area(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  using subCmd = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  std::unordered_map< std::string, subCmd > subCmds;
  subCmds["EVEN"] = areaEvenCmd;
  subCmds["ODD"] = areaOddCmd;
  subCmds["MEAN"] = areaMeanCmd;
  try
  {
    subCmds.at(arg)(polygons, output);
  }
  catch (const std::out_of_range&)
  {
    areaVertexesCmd(polygons, std::stoull(arg), output);
  }
}

void serter::min(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  using subCmd = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  std::unordered_map< std::string, subCmd > subCmds;
  subCmds["AREA"] = minAreaCmd;
  subCmds["VERTEXES"] = minVertexesCmd;
  try
  {
    subCmds.at(arg)(polygons, output);
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("Invalid arg");
  }
}

void serter::max(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  using subCmd = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  std::unordered_map< std::string, subCmd > subCmds;
  subCmds["AREA"] = maxAreaCmd;
  subCmds["VERTEXES"] = maxVertexesCmd;
  try
  {
    subCmds.at(arg)(polygons, output);
  }
  catch (const std::out_of_range&)
  {
    throw std::invalid_argument("Invalid arg");
  }
}

void serter::count(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  std::string arg;
  input >> arg;
  using subCmd = std::function< void(const std::vector< Polygon >&, std::ostream&) >;
  std::unordered_map< std::string, subCmd > subCmds;
  subCmds["EVEN"] = countEvenCmd;
  subCmds["ODD"] = countOddCmd;
  try
  {
    subCmds.at(arg)(polygons, output);
  }
  catch (const std::out_of_range&)
  {
    countVertexesCmd(polygons, std::stoull(arg), output);
  }
}

void serter::echo(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon polygon;
  input >> polygon;
  if (!input)
  {
    throw std::invalid_argument("Invalid arg");
  }
  size_t countEcho = std::count(polygons.begin(), polygons.end(), polygon);
  std::vector< Polygon > temp(polygons.size() + countEcho);
  size_t sameCount = 0;
  for (const auto& figure: polygons)
  {
    temp.push_back(figure);
    if (figure == polygon)
    {
      ++sameCount;
      temp.push_back(polygon);
    }
  }
  polygons = temp;
  output << sameCount << '\n';
}

void serter::rmEcho(std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  Polygon poly;
  input >> poly;
  if (!input)
  {
    throw std::invalid_argument("Invalid arg");
  }
  auto pred = std::bind(isEqualPolygon, _1, _2, poly);
  auto new_end = std::unique(polygons.begin(), polygons.end(), pred);
  size_t res = std::distance(new_end, polygons.end());
  polygons.erase(new_end, polygons.end());
  FormatGuard iofmtguard(output);
  output << std::fixed << std::setprecision(1);
  output << res << "\n";
}

void serter::lessArea(const std::vector< Polygon >& polygons, std::istream& input, std::ostream& output)
{
  Polygon poly;
  input >> poly;
  using namespace std::placeholders;
  if (std::cin)
  {
    output << std::count_if(std::begin(polygons), std::end(polygons), std::bind(isLessByArea, _1, poly)) << '\n';
  }
  else
  {
    throw std::invalid_argument("Invalid arg");
  }
}



