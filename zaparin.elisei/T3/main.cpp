#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, const char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: invalid argument\n";
    return 1;
  }

  std::ifstream fin(argv[1]);
  if (!fin.is_open())
  {
    std::cerr << "Error: invalid filename\n";
    return 2;
  }

  using namespace zaparin;

  std::vector< Polygon > polygons;
  using in_it = std::istream_iterator< Polygon >;
  using limits = std::numeric_limits< std::streamsize >;

  while (!fin.eof())
  {
    std::copy(in_it{ fin }, in_it{}, std::back_inserter(polygons));
    fin.clear();
    fin.ignore(limits::max(), '\n');
  }
}