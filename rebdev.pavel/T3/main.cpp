#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <limits>

#include "polygon.hpp"
#include "commands.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "I work only with one programm argumet!";
    return 1;
  }

  std::ifstream inFile(argv[1]);
  using inputItT = std::istream_iterator< rebdev::Polygon >;
  using polyVec = std::vector< rebdev::Polygon >;
  polyVec polygonsVector(inputItT{ inFile }, inputItT{});

  std::map< std::string, std::function< void(const polyVec &, std::ostream &) > > commandMap;
  commandMap["AREA EVEN"] = rebdev::areaEven;
  commandMap["AREA ODD"] = rebdev::areaOdd;
  commandMap["AREA MEAN"] = rebdev::areaMean;
  size_t param = 0;
  using namespace std::placeholders;
  commandMap["AREA NUM"] = std::bind(rebdev::areaNum, param, _1, _2);
  commandMap["MAX AREA"] = rebdev::maxArea;
  commandMap["MAX VERTEXES"] = rebdev::maxVertexes;
  commandMap["MIN AREA"] = rebdev::minArea;
  commandMap["MIN VERTEXES"] = rebdev::minVertexes;
  commandMap["COUNT EVEN"] = rebdev::countEven;
  commandMap["COUNT ODD"] = rebdev::countOdd;
  commandMap["COUNT NUM"] = std::bind(rebdev::countNum, param, _1, _2);
  commandMap["RECTS"] = rebdev::rects;
  commandMap["INFRAME"] = std::bind(rebdev::inframe, _1, std::ref(std::cin), _2);

  std::string inStr;
  while (std::cin >> inStr)
  {
    try
    {
      commandMap.at(inStr)(polygonsVector, std::cout);
    }
    catch (std::out_of_range & e)
    {
      std::string secondInStr;
      std::cin >> secondInStr;

      if (std::isdigit(secondInStr[0]))
      {
        inStr += " NUM";
        param = (secondInStr[0] - '0');
      }
      else
      {
        inStr += (" " + secondInStr);
      }

      try
      {
          commandMap.at(inStr)(polygonsVector, std::cout);
      }
      catch (std::out_of_range & e)
      {
        std::cerr << "<INVALID COMMAND>\n";
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    param = 0;
  }
  return 0;
}
