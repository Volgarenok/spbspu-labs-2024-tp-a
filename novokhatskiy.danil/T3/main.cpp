#include <iostream>
#include <limits>
#include <vector>
#include <iterator>
#include "polygon.hpp"
#include "StreamGuard.hpp"

void inputPolygons(std::istream& in, std::vector< novokhatskiy::Polygon >& v)
{
  using inIt = std::istream_iterator< novokhatskiy::Polygon >;
  while (!in.eof())
  {
    std::copy(inIt{ in }, inIt{}, std::back_inserter(v));
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

int main()
{
  using namespace novokhatskiy;
  std::vector< Polygon > res = {};
  inputPolygons(std::cin, res);
  for (auto i = res.cbegin(); i != res.cend(); i++)
  {
    std::cout << *i << ' ';
  }
  std::cout << "Hello World!\n";
}
