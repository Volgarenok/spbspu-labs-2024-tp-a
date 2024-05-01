#include "polygon.hpp"
#include <iterator>
#include <algorithm>
#include <numeric>
#include "point.hpp"

std::istream& zaparin::operator>>(std::istream& in, Polygon& plg)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  Point pointTemp{ 0, 0 };
  Polygon plgTemp;
  int pointsCount = 0;
  in >> pointsCount;


  for (int i = 0; (i < pointsCount) && in; i++)
  {
    in >> pointTemp;
    plgTemp.points.push_back(pointTemp);
  }

  if (in)
  {
    plg = plgTemp;
  }

  return in;
}

std::ostream& zaparin::operator<<(std::ostream& out, const Polygon& plg)
{
  using out_it = std::ostream_iterator< Point >;

  std::copy(plg.points.begin(), plg.points.end(), out_it{ out, " " });

  return out;
}

bool zaparin::operator==(const Polygon& plg1, const Polygon& plg2)
{
  return (plg1.points == plg2.points);
}

const zaparin::Point& zaparin::TriangleArea::operator()(const Point& p2, const Point& p3)
{
  double a = getLength(p1, p2);
  double b = getLength(p2, p3);
  double c = getLength(p1, p3);
  double p = (a + b + c) / 2;
  area += std::sqrt(p * (p - a) * (p - b) * (p - c));
  return p3;
}

double zaparin::getArea(const Polygon& plg)
{
  TriangleArea accArea{ 0.0, plg.points[0] };
  std::accumulate(plg.points.begin() + 2, plg.points.end(), plg.points[1], std::ref(accArea));
  return accArea.area;
}

void zaparin::PolygonsArea::operator()(const Polygon& plg)
{
  area += getArea(plg);
}

bool zaparin::isEven(const Polygon& plg)
{
  return ((plg.points.size() % 2) == 0);
}

bool zaparin::isOdd(const Polygon& plg)
{
  return ((plg.points.size() % 2) == 1);
}

bool zaparin::isNov::operator()(const Polygon& plg)
{
  return (nov == plg.points.size());
}

void zaparin::MaxArea::operator()(const Polygon& plg)
{
  double newArea = getArea(plg);
  if (newArea > area)
  {
    area = newArea;
  }
}

void zaparin::MaxVertexes::operator()(const Polygon& plg)
{
  size_t newVertexes = plg.points.size();
  if (newVertexes > vertexes)
  {
    vertexes = newVertexes;
  }
}

void zaparin::MinArea::operator()(const Polygon& plg)
{
  double newArea = getArea(plg);
  if (newArea < area)
  {
    area = newArea;
  }
}

void zaparin::MinVertexes::operator()(const Polygon& plg)
{
  size_t newVertexes = plg.points.size();
  if (newVertexes < vertexes)
  {
    vertexes = newVertexes;
  }
}

void zaparin::Counter::operator()(const Polygon& plg)
{
  if (func(plg))
  {
    num++;
  }
}

void zaparin::MaxSeq::operator()(const Polygon& plg)
{
  if (MaxSeqplg == plg)
  {
    counter++;
    if (counter > maxCounter)
    {
      maxCounter = counter;
    }
  }
  else
  {
    counter = 0;
  }
}

zaparin::Segment zaparin::MakeSegment::operator()(const Point& currPoint)
{
  Segment newSeg{ prevPoint, currPoint };
  prevPoint = currPoint;
  return newSeg;
}

int zaparin::vectorCrossProduct(const std::vector< int >& vec1, const std::vector< int >& vec2)
{
  return (vec1[0] * vec2[1] - vec2[0] * vec1[1]);
}

bool zaparin::isSegmentsIntersected(const Segment& ab, const Segment& cd)
{
  std::vector< int > vector_ab = { (ab.p2.x - ab.p1.x), (ab.p2.y - ab.p1.y) };
  std::vector< int > vector_ac = { (cd.p1.x - ab.p1.x), (cd.p1.y - ab.p1.y) };
  std::vector< int > vector_ad = { (cd.p2.x - ab.p1.x), (cd.p2.y - ab.p1.y) };

  std::vector< int > vector_cd = { (cd.p2.x - cd.p1.x), (cd.p2.y - cd.p1.y) };
  std::vector< int > vector_ca = { (ab.p1.x - cd.p1.x), (ab.p1.y - cd.p1.y) };
  std::vector< int > vector_cb = { (ab.p2.x - cd.p1.x), (ab.p2.y - cd.p1.y) };

  int d1 = vectorCrossProduct(vector_ab, vector_ac);
  int d2 = vectorCrossProduct(vector_ab, vector_ad);
  int d3 = vectorCrossProduct(vector_cd, vector_cd);
  int d4 = vectorCrossProduct(vector_cd, vector_cb);

  if (((d1 <= 0 && d2 >= 0) || (d1 >= 0 && d2 <= 0)) &&
      ((d3 <= 0 && d4 >= 0) || (d3 >= 0 && d4 <= 0)))
  {
    return 1;
  }
  return 0;
}

bool zaparin::isPolygonsIntersected(const Polygon& plg1, const Polygon& plg2)
{
  std::vector< Segment > vecOfSeg1;
  std::vector< Segment > vecOfSeg2;

  std::transform(plg1.points.begin() + 1, plg1.points.end(), std::back_inserter(vecOfSeg1), MakeSegment{ plg1.points[0] });
  std::transform(plg2.points.begin() + 1, plg2.points.end(), std::back_inserter(vecOfSeg2), MakeSegment{ plg2.points[0] });

  for (int i = 0; i < vecOfSeg1.size(); i++)
  {
    for (int j = 0; j < vecOfSeg2.size(); j++)
    {
      if (isSegmentsIntersected(vecOfSeg1[i], vecOfSeg2[j]))
      {
        return 1;
      }
    }
  }
  return 0;
}

void zaparin::IsIntersected::operator()(const Polygon& plg2)
{
  if (isPolygonsIntersected(plg1, plg2))
  {
    intersectionsCount++;
  }
}
