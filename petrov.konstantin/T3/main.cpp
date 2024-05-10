#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <limits>
#include "Geometry.hpp"
#include "Commands.hpp"
#include "UserInterface.hpp"

template <class T>
std::vector< T >& readFromFile(std::istream& fin, std::vector< T >& dest)
{
  while (!fin.eof())
  {
    std::istream_iterator< T > finItFirst(fin);
    std::istream_iterator< T > finItLast;
    std::copy(finItFirst, finItLast, std::back_inserter(dest));
    if (fin.fail())
    {
      fin.clear();
      using numLim = std::numeric_limits< std::streamsize >;
      fin.ignore(numLim::max(), '\n');
    }
  }
  return dest;
}

std::ostream& getExtremumTests(std::ostream& out, std::vector< petrov::Polygon >& src)
{
  bool forArea = false;
  bool forMax = false;
  size_t interconections = 4;
  for (size_t i = 0; i < interconections; ++i)
  {
    forArea = i < (interconections / 2);
    forMax = i % 2 != 0;
    out << (forMax ? "Maximum " : "Minimum ");
    out << (forArea ? "area: " : "number of vertexes: ");
    out << petrov::getExtremum(src, forArea, forMax) << '\n';
  }
  return out;
}

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    std::cout << "No arguments provided\n";
    return 0;
  }

  using petrov::Polygon;
  std::ifstream fin(argv[1], std::ios::in);
  std::vector< Polygon > polygons;
  readFromFile(fin, polygons);
  fin.close();

  std::ostream_iterator< Polygon > coutIt(std::cout, "\n");
  std::copy(polygons.begin(), polygons.end(), coutIt);

  std::cout << '\n';
  petrov::run(std::cin, std::cout, polygons);
  // std::cout << '\n';
  // getExtremumTests(std::cout, polygons);
}
