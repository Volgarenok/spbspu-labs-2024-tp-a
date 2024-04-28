#include <iostream>
#include <limits>
#include <vector>
#include <map>
#include <iterator>
#include <functional>
#include "polygon.hpp"
#include "commandsSolving.hpp"
#include "StreamGuard.hpp"

int main(int argc, char** argv)
{
  /*if (argc < 2)
  {
    std::cerr << "Wrong input argument\n";
    return 1;
  }*/
  using namespace novokhatskiy;
  std::vector< Polygon > polygons;
  using inIt = std::istream_iterator< novokhatskiy::Polygon >;
  while (!std::cin.eof())
  {
    std::copy(inIt{ std::cin }, inIt{}, std::back_inserter(polygons));
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::string argumemt;
  std::cin >> argumemt;
  std::map< std::string, std::function< void() > map;
  {

  }

  /*std::vector< Polygon > res = {};
  inputPolygons(std::cin, res);
  for (auto i = res.cbegin(); i != res.cend(); i++)
  {
    std::cout << *i << ' ';
  }*/
  std::cout << "Hello World!\n";
}
