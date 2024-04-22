#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>

#include "polygon.hpp"

int main()
{
  std::vector< ibragimov::Polygon > test;
  std::ifstream ifs("input.txt");

  if (ifs.is_open())
  {
    using is_iter = std::istream_iterator< ibragimov::Polygon >;
    std::copy(is_iter{ifs}, is_iter{}, std::back_inserter(test));
    if (!ifs)
    {
      ifs.clear();
      ifs.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    ifs.close();
  }

  // std::cout << test.size() << '\n';
  // for (size_t i = 0; i < test.size(); ++i)
  // {
  //   for (size_t j = 0; j < test[i].points.size(); ++j)
  //   {
  //     std::cout << test[i].points[j].x << test[i].points[j].y << ' ';
  //   }
  //   std::cout << '\n';
  // }

  return 0;
}
