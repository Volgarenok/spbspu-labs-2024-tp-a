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
void rebdev::areaBase(std::istream & in, std::ostream & out, const polyVec & vec)
{
  std::string str;
  in >> str;
  polyVec vecCopy(vec.size());
  polyVec::iterator it;
  try
  {
    long long int num = std::stoll(str);
    auto areaN = std::bind(areaNum, std::placeholders::_1, num);
    it = std::copy_if(vec.begin(), vec.end(), vecCopy.begin(), areaN);
  }
  catch (const std::exception & e)
  {
    if(str == "EVEN")
    {
      it = std::copy_if(vec.begin(), vec.end(), vecCopy.begin(), areaEven);
    }
    else if(str == "ODD")
    {
      it = std::copy_if(vec.begin(), vec.end(), vecCopy.begin(), std::not_fn(areaEven));
    }
    else if(str == "MEAN")
    {
      it = vecCopy.end();
    }
    else
    {
      throw std::out_of_range("Unknown command!");
    }
  }
  std::vector< double > squareVec(vec.size());
  std::transform(vecCopy.begin(), it, squareVec.begin(), polygonArea);
  double area = std::accumulate(squareVec.begin(), squareVec.end(), 0);
  if (it == vecCopy.end())
  {
    area /= vec.size();
  }
  out << area << '\n';
}
void rebdev::maxBase(std::istream & in, std::ostream & out, const polyVec & vec)
{

}
void rebdev::minBase(std::istream & in, std::ostream & out, const polyVec & vec)
{

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
