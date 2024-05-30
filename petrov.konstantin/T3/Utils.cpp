#include "Utils.hpp"
#include <algorithm>
#include "Geometry.hpp"

bool petrov::isEven(const Polygon& p)
{
  return p.points.size() % 2 == 0;
}
bool petrov::isOdd(const Polygon& p)
{
  return p.points.size() % 2 != 0;
}
bool petrov::myIsdigit(char symbol)
{
  return std::isdigit(static_cast< unsigned char >(symbol));
}
bool petrov::isStringANumber(std::string str)
{
  return std::find_if_not(str.cbegin(), str.cend(), myIsdigit) == str.cend();
}
