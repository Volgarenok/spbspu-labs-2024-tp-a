#include <fstream>
#include <iostream>
#include <streamGuard.hpp>
#include "polygon.hpp"

int main(int argc, char **argv)
{
  using namespace allaberdiev;
  if (argc < 2)
  {
    std::cerr << "<NOT ENOUGH ARGUMENTS>\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    return 1;
  }

 std::vector< Polygon > polygons;

  using input_it = std::istream_iterator< Polygon >;
  while (!file.eof())
  {
    std::copy(input_it{ file }, input_it{}, std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  file.close();

}
