#include <iostream>
#include <limits>
#include <vector>
#include <iterator>
#include "polygon.hpp"
#include "StreamGuard.hpp"

// void inputPolygons(std::istream& in, std::vector< novokhatskiy::Polygon >& v)
// {
//   using inIt = std::istream_iterator< novokhatskiy::Polygon >;
//   while (!in.eof())
//   {
//     std::copy(inIt{ in }, inIt{}, std::back_inserter(v));
//     in.clear();
//     in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//   }
// }

struct SolvingCommands
{
};

struct AccumulateArea
{
  novokhatskiy::Point p1;
  double operator()(double &res, const novokhatskiy::Point &p2, const novokhatskiy::Point &p3)
  {
    res += 0.5 * (std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)));
    return res;
  }
}

int
main()
{
  using namespace novokhatskiy;
  // std::vector< Polygon > res = {};
  // inputPolygons(std::cin, res);
  // for (auto i = res.cbegin(); i != res.cend(); i++)
  // {
  //   std::cout << *i << ' ';
  // }
  // std::cout << "Hello World!\n";
}
