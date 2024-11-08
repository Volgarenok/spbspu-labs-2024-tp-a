#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "Commands.h"
#include "DataStruct.h"

int main()
{
  std::vector< stepanov::Polygon > polygons;

  std::istringstream iss(
    "3\n(0;0) (0;2) (2;2)\n"
    "4\n(1;1) (1;3) (3;3) (3;1)\n"
    "5\n(2;2) (2;4) (4;4) (4;2) (3;3)\n"
    "6\n(3;3) (3;5) (5;5) (5;3) (4;4) (4;3)\n"
  );

  stepanov::Polygon p;
  while (iss >> p)
  {
    polygons.push_back(p);
  }
  stepanov::getAreaEven(polygons, std::cout);
  stepanov::getAreaOdd(polygons, std::cout);
  stepanov::getAreaMean(polygons, std::cout);
  stepanov::getAreaVertexes(polygons, 3 ,std::cout);
  stepanov::getMaxArea(polygons, std::cout);
  stepanov::getMaxVertexes(polygons, std::cout);
  stepanov::getMinArea(polygons, std::cout);
  stepanov::getMinVertexes(polygons, std::cout);
  stepanov::getCountEven(polygons, std::cout);


  return 0;
  }
