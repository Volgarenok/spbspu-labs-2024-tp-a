#ifndef COMMANDS_SOLVING_HPP
#define COMMANDS_SOLVING_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include "polygon.hpp"

namespace novokhatskiy
{
  struct CmdArgs
  {
    std::vector< Polygon >& points;
    std::istream& in;
    std::ostream& out;
  };

  void commandArea(const std::vector< Polygon >& polygons, std::istream& in)
  {
    std::string arg;
    in >> arg;
    std::function< double(double, const Polygon&) > areamain;
    if (arg == "EVEN")
    {
      using namespace std::placeholders;
      auto area = std::bind(AccumulateEvenOrOddArea{}, _1, _2, true);
    }
    else if (arg == "ODD")
    {
      using namespace std::placeholders;
      auto area = std::bind(AccumulateEvenOrOddArea{}, _1, _2, false);
    }
    else if (arg == "MEAN")
    {
      using namespace std::placeholders;
      auto area = std::bind(AccumulateMeanArea{}, _1, _2);
    }
    else
    {

    }
  }
  
  struct AccumulateEvenOrOddArea
  {
    double operator()(double res, const Polygon& p, bool isEven)
    {
      if (isEven == (p.points.size() % 2 == 0))
      {
        res += p.getArea();
      }
      return res;
    }
  };

  struct AccumulateMeanArea
  {
    double operator()(double res, const Polygon& p)
    {
      if (p.points.size() < 1)
      {
        throw std::logic_error("To accumulate mean area, we need to have more than 1 shape"); // заменить на invalid_argument
      }
      return res + (p.getArea() / p.points.size());
    }
  };

  struct AccumulateArea
  {
    novokhatskiy::Point p1;
    double operator()(double& res, const novokhatskiy::Point& p2, const novokhatskiy::Point& p3)
    {
      res += 0.5 * (std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)));
      p1 = p2;
      return res;
    }
  };
}

#endif
