#include "commands.hpp"
#include <algorithm>
#include <stream_guard.hpp>
#include <functional>
#include "polygon.hpp"

bool isEven(namestnikov::Polygon polygon)
{
  return (polygon.points.size() % 2);
}

bool isOdd(namestnikov::Polygon polygon)
{
  return !isEven(polygon);
}

bool isProperSize(namestnikov::Polygon polygon, size_t number)
{
  return (polygon.points.size() == number);
}

void namestnikov::getCount(std::vector< namestnikov::Polygon > & data, std::istream & in, std::ostream & out)
{
  std::string argument = "";
  in >> argument;
  if (argument == "EVEN")
  {
    out << std::count_if(data.begin(), data.end(), isEven);
  }
  else if (argument == "ODD")
  {
    out << std::count_if(data.begin(), data.end(), isOdd);
  }
  else
  {
    try
    {
      size_t pointsCount = std::stoull(argument);
      if (pointsCount < 3)
      {
         throw std::logic_error("Wrong number of points");
      }
      std::function< bool(namestnikov::Polygon) > isRightCount = std::bind(isProperSize, _1, pointsCount);
      out << std::count_if(data.begin(), data.end(), isRightCount);
    }
    catch (const std::invalid_argument &)
    {
      out << "<INVALID COMMAND>";
    }   
  }
}