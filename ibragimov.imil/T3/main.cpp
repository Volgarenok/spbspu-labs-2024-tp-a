#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#include "commands.hpp"
#include "polygon.hpp"

int main()
{
  std::vector< ibragimov::Polygon > polygons = {};

  std::ifstream ifs("input.txt");
  if (ifs.is_open())
  {
    using is_iter = std::istream_iterator< ibragimov::Polygon >;
    std::copy(is_iter{ifs}, is_iter{}, std::back_inserter(polygons));
    if (!ifs)
    {
      ifs.clear();
      ifs.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    ifs.close();
  }

  std::string command = "";
  std::map< std::string, std::function< double(const std::vector< ibragimov::Polygon >&) > > commands;
  commands["AREA"] = ibragimov::calculateArea;
  // commands["MAX"] = ibragimov::findMax;
  // commands["MIN"] = ibragimov::findMin;
  // commands["COUNT"] = ibragimov::count;
  while (std::cin >> command)
  {
    try
    {
      int test = commands.at(command)(polygons);
      std::cout << test << '\n';
    }
    catch (...)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
