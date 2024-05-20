#include "Commands.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <string>
#include "Geometry.hpp"
#include "Utils.hpp"

void petrov::cmdArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }

  std::string arg;
  in >> arg;

  if (arg == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::logic_error("<NO POLYGONS>");
    }
    out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, AccPolygonArea) / polygons.size() << '\n';
    return;
  }

  std::function<double(double, const Polygon&)> areaAcc = nullptr;
  using namespace std::placeholders;
  if (isStringANumber(arg))
  {
    std::size_t numOfVertexes = static_cast< std::size_t >(std::stoi(arg));
    if (numOfVertexes < 3)
    {
      throw std::logic_error("<CANT BE LESS THAN 3 VERTEXES>");
    }
    areaAcc = std::bind(&AccPolygonAreaNumOfVertexes, _1, _2, numOfVertexes);
  }
  else
  {
    bool forEven = true;
    if (arg == "EVEN")
    {
      forEven = true;
    }
    else if (arg == "ODD")
    {
      forEven = false;
    }
    else
    {
      throw std::invalid_argument("<INVALID ARGUMENT>");
    }
    areaAcc = std::bind(&AccPolygonAreaEO, _1, _2, forEven);
  }
  out << std::accumulate(polygons.cbegin(), polygons.cend(), 0.0, areaAcc) << '\n';
}
void petrov::cmdExtremum(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out, bool forMax)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }

  std::string arg;
  in >> arg;
  bool forArea = true;
  bool(*comp)(const Polygon&, const Polygon&) = nullptr;
  if (arg == "AREA")
  {
    comp = isSmallerPolygonArea;
    forArea = true;
  }
  else if (arg == "VERTEXES")
  {
    comp = isSmallerNumOfVertexes;
    forArea = false;
  }
  else
  {
    throw std::invalid_argument("<INVALID ARGUMENT>");
  }

  using iter = std::vector< Polygon >::const_iterator;
  using compType = bool(*)(const Polygon&, const Polygon&);
  using extElemType = iter(*)(iter, iter, compType);
  extElemType extremumElement = nullptr;
  if (forMax)
  {
    extremumElement = std::max_element;
  }
  else
  {
    extremumElement = std::min_element;
  }

  auto polIterator = extremumElement(polygons.cbegin(), polygons.cend(), comp);
  if (polIterator == polygons.cend())
  {
    throw std::logic_error("<NO SUCH VERTEXES>");
  }

  if (forArea)
  {
    out << getArea(*polIterator);
  }
  else
  {
    out << (*polIterator).points.size();
  }
  out << '\n';
}
void petrov::cmdCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }

  std::string arg;
  in >> arg;
  std::function< bool(const Polygon&) > comp = nullptr;
  if (isStringANumber(arg))
  {
    std::size_t numOfVertexes = static_cast< std::size_t >(std::stoi(arg));
    if (numOfVertexes < 3)
    {
      throw std::logic_error("<CANT BE LESS THAN 3 VERTEXES>");
    }
    using namespace std::placeholders;
    comp = std::bind(&isEqualNOV, _1, numOfVertexes);
  }
  else
  {
    if (arg == "EVEN")
    {
      comp = isEven;
    }
    else if (arg == "ODD")
    {
      comp = isOdd;
    }
    else
    {
      throw std::invalid_argument("<INVALID ARGUMENT>");
    }
  }

  out << static_cast< size_t >(std::count_if(polygons.cbegin(), polygons.cend(), comp)) << '\n';
}
void petrov::cmdRmEcho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }

  Polygon mask;
  in >> mask;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID ARGUMENT>");
  }
  if (mask.points.size() < 3)
  {
    throw std::logic_error("<MASK CANT HAVE LESS THAN 3 VERTEXES>");
  }
  auto tmp = std::unique(polygons.begin(), polygons.end(), EqualPol{ mask });
  size_t count = std::distance(tmp, polygons.end());
  polygons.erase(tmp, polygons.end());
  out << count << '\n';
}
void petrov::cmdSame(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }

  Polygon mask;
  in >> mask;
  if (!in || in.peek() != '\n')
  {
    throw std::invalid_argument("<INVALID ARGUMENT>");
  }
  if (mask.points.size() < 3)
  {
    throw std::logic_error("<MASK CANT HAVE LESS THAN 3 VERTEXES>");
  }
  using namespace std::placeholders;
  auto comp = std::bind(&isSame, _1, mask);
  out << std::count_if(polygons.cbegin(), polygons.cend(), comp) << '\n';
}
