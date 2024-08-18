#include "commands.hpp"

#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

bool areaNum(const rebdev::Polygon & poly, long long int num)
{
  return (poly.points.size() == num);
}
bool areaEven(const rebdev::Polygon & poly)
{
  return ((poly.points.size() % 2) == 0);
}
bool areaOdd(const rebdev::Polygon & poly)
{
  return ((poly.points.size() % 2) != 0);
}
void rebdev::areaBase(std::istream & in, std::ostream & out, const polyVec & vec)
{
  std::string str;
  in >> str;
  polyVec vecCopy(vec.size());
  polyVec::iterator it;
  try
  {
    auto num = std::stoull(str);
    auto areaN = std::bind(areaNum, std::placeholders::_1, num);
    it = std::copy_if(vec.begin(), vec.end(), vecCopy.begin(), areaN);
  }
  catch (const std::exception & e)
  {
    if (str == "EVEN")
    {
      it = std::copy_if(vec.begin(), vec.end(), vecCopy.begin(), areaEven);
    }
    else if (str == "ODD")
    {
      it = std::copy_if(vec.begin(), vec.end(), vecCopy.begin(), areaOdd);
    }
    else if (str == "MEAN")
    {
      vecCopy = vec;
      it = vecCopy.end();
    }
    else
    {
      throw std::out_of_range("Unknown command!");
    }
  }
  std::vector< double > areaVec(vec.size());
  std::transform(vecCopy.begin(), it, areaVec.begin(), polygonArea);
  double area = std::accumulate(areaVec.begin(), areaVec.end(), 0);
  if (it == vecCopy.end())
  {
    area /= vec.size();
  }
  out << area << '\n';
}
using areaFunc = std::function< double(const std::vector< double > &) >;
using vertFunc = std::function< size_t(const std::vector< size_t > &) >;
void maxMinBase(std::istream & in, std::ostream & out, const rebdev::polyVec & vec, areaFunc ar, vertFunc vert)
{
  std::string str;
  in >> str;
  if (str == "AREA")
  {
    std::vector< double > areaVec(vec.size());
    std::transform(vec.begin(), vec.end(), areaVec.begin(), rebdev::polygonArea);
    double area = ar(areaVec);
    std::cout << area << '\n';
  }
  else if (str == "VERTEXES")
  {
    std::vector< size_t > vertexesVec(vec.size());
    std::transform(vec.begin(), vec.end(), vertexesVec.begin(), rebdev::polygonVert);
    size_t vertex = vert(vertexesVec);
    std::cout << vertex << '\n';
  }
  else
  {
    throw std::out_of_range("Unknown command!");
  }
}
double maxArea(const std::vector< double > & areaVec)
{
  return (*std::max_element(areaVec.begin(), areaVec.end()));
}
double maxVertexes(const std::vector< size_t > & vertexesVec)
{
  return (*std::max_element(vertexesVec.begin(), vertexesVec.end()));
}
void rebdev::maxBase(std::istream & in, std::ostream & out, const polyVec & vec)
{
  maxMinBase(in, out, vec, maxArea, maxVertexes);
}
double minArea(const std::vector< double > & areaVec)
{
  return (*std::min_element(areaVec.begin(), areaVec.end()));
}
double minVertexes(const std::vector< size_t > & vertexesVec)
{
  return (*std::min_element(vertexesVec.begin(), vertexesVec.end()));
}
void rebdev::minBase(std::istream & in, std::ostream & out, const polyVec & vec)
{
  maxMinBase(in, out, vec, minArea, minVertexes);
}
void rebdev::countBase(std::istream & in, std::ostream & out, const polyVec & vec)
{

}
void rebdev::rects(std::istream & in, std::ostream & out, const polyVec & vec)
{

}
void rebdev::inframe(std::istream & in, std::ostream & out, const polyVec & vec)
{

}
