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
    size_t numOfVertexes = static_cast< size_t >(std::stoi(arg));
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
void petrov::cmdMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }

  std::string arg;
  in >> arg;
  if (arg == "AREA")
  {
    auto polIt = std::max_element(polygons.cbegin(), polygons.cend(), isSmallerPolygonArea);
    if (polIt == polygons.cend())
    {
      throw std::logic_error("<NO SUCH AREA>");
    }
    out << getArea(*polIt) << '\n';
  }
  else if (arg == "VERTEXES")
  {
    auto polIt = std::max_element(polygons.cbegin(), polygons.cend(), isSmallerNumOfVertexes);
    if (polIt == polygons.cend())
    {
      throw std::logic_error("<NO SUCH VETEXES>");
    }
    out << (*polIt).points.size() << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID ARGUMENT>");
  }
}
void petrov::cmdMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return;
  }

  std::string arg;
  in >> arg;
  if (arg == "AREA")
  {
    auto polIt = std::min_element(polygons.cbegin(), polygons.cend(), isSmallerPolygonArea);
    if (polIt == polygons.cend())
    {
      throw std::logic_error("<NO SUCH AREA>");
    }
    out << getArea(*polIt) << '\n';
  }
  else if (arg == "VERTEXES")
  {
    auto polIt = std::min_element(polygons.cbegin(), polygons.cend(), isSmallerNumOfVertexes);
    if (polIt == polygons.cend())
    {
      throw std::logic_error("<NO SUCH VETEXES>");
    }
    out << (*polIt).points.size() << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID ARGUMENT>");
  }
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
    size_t numOfVertexes = static_cast< size_t >(std::stoi(arg));
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
