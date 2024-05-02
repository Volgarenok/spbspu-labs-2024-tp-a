#include "commands.hpp"
#include <algorithm>
#include <numeric>
#include <string>
#include "polygon.hpp"

void zaparin::cmdArea(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream&, std::ostream& out, std::string&& parameter)
{
  if (parameter == "EVEN")
  {
    std::vector< Polygon > evenPolygons;
    std::copy_if(std::begin(plgs), std::end(plgs), std::back_inserter(evenPolygons), isEven);

    PolygonsArea polygonsArea{ 0.0 };
    std::for_each(evenPolygons.begin(), evenPolygons.end(), std::ref(polygonsArea));
    out << std::fixed;
    out.precision(1);
    out << polygonsArea.area << "\n";
  }

  if (parameter == "ODD")
  {
    std::vector< Polygon > oddPolygons;
    std::copy_if(std::begin(plgs), std::end(plgs), std::back_inserter(oddPolygons), isOdd);

    PolygonsArea polygonsArea{ 0.0 };
    std::for_each(oddPolygons.begin(), oddPolygons.end(), std::ref(polygonsArea));
    out << std::fixed;
    out.precision(1);
    out << polygonsArea.area << "\n";
  }

  if (parameter == "MEAN")
  {
    PolygonsArea polygonsArea{ 0.0 };
    std::for_each(plgs.begin(), plgs.end(), std::ref(polygonsArea));
    out << std::fixed;
    out.precision(1);
    out << (polygonsArea.area / plgs.size()) << "\n";
  }

  if (parameter == "NOV")
  {
    std::vector< Polygon > novPolygons;
    std::copy_if(std::begin(plgs), std::end(plgs), std::back_inserter(novPolygons), isNov{numOfVertexes});

    PolygonsArea polygonsArea{ 0.0 };
    std::for_each(novPolygons.begin(), novPolygons.end(), std::ref(polygonsArea));
    out << std::fixed;
    out.precision(1);
    out << polygonsArea.area << "\n";
  }
}

void zaparin::cmdMax(std::vector< Polygon > plgs, size_t, std::istream&, std::ostream& out, std::string&& parameter)
{
  if (parameter == "AREA")
  {
    MaxArea maxArea;
    std::for_each(plgs.begin(), plgs.end(), std::ref(maxArea));
    out << std::fixed;
    out.precision(1);
    out << maxArea.area << "\n";
  }
  if (parameter == "VERTEXES")
  {
    MaxVertexes maxVertexes;
    std::for_each(plgs.begin(), plgs.end(), std::ref(maxVertexes));
    out << std::fixed;
    out.precision(1);
    out << maxVertexes.vertexes << "\n";
  }
}

void zaparin::cmdMin(std::vector< Polygon > plgs, size_t, std::istream&, std::ostream& out, std::string&& parameter)
{
  if (parameter == "AREA")
  {
    MinArea minArea{ getArea(plgs[0]) };
    std::for_each(plgs.begin() + 1, plgs.end(), std::ref(minArea));
    out << std::fixed;
    out.precision(1);
    out << minArea.area << "\n";
  }
  if (parameter == "VERTEXES")
  {
    MinVertexes minVertexes{ plgs[0].points.size() };
    std::for_each(plgs.begin() + 1, plgs.end(), std::ref(minVertexes));
    out << std::fixed;
    out.precision(1);
    out << minVertexes.vertexes << "\n";
  }
}

void zaparin::cmdCount(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream&, std::ostream& out, std::string&& parameter)
{
  if (parameter == "EVEN")
  {
    Counter isEvenCount{ 0, isEven };
    std::for_each(plgs.begin(), plgs.end(), std::ref(isEvenCount));
    out << std::fixed;
    out.precision(1);
    out << isEvenCount.num << "\n";
  }
  if (parameter == "ODD")
  {
    Counter isEvenCount{ 0, isOdd };
    std::for_each(plgs.begin(), plgs.end(), std::ref(isEvenCount));
    out << std::fixed;
    out.precision(1);
    out << isEvenCount.num << "\n";
  }
  if (parameter == "NOV")
  {
    Counter isEvenCount{ 0, isNov{ numOfVertexes } };
    std::for_each(plgs.begin(), plgs.end(), std::ref(isEvenCount));
    out << std::fixed;
    out.precision(1);
    out << isEvenCount.num << "\n";
  }
}

void zaparin::cmdMaxSeq(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out)
{
  Polygon plg;
  std::vector< Point > temp;

  using in_it = std::istream_iterator< Point >;
  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(temp));

  plg.points = temp;

  MaxSeq maxSeq{ plg };
  std::for_each(plgs.begin(), plgs.end(), std::ref(maxSeq));
  out << std::fixed;
  out.precision(1);
  out << maxSeq.maxCounter << "\n";
}

void zaparin::cmdIntersections(std::vector< Polygon > plgs, size_t numOfVertexes, std::istream& in, std::ostream& out)
{
  Polygon plg;
  std::vector< Point > temp;

  using in_it = std::istream_iterator< Point >;
  std::copy_n(in_it{ in }, numOfVertexes, std::back_inserter(temp));

  plg.points = temp;

  IsIntersected PlgIntersected{ plg };
  std::for_each(plgs.begin(), plgs.end(), std::ref(PlgIntersected));

  out << PlgIntersected.intersectionsCount << "\n";
}

bool zaparin::isNumeric(const std::string& str)
{
  char arr[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
  for (int i = 0; i < 10; i++)
  {
    if (str[0] == arr[i])
    {
      return 1;
    }
  }
  return 0;
}

