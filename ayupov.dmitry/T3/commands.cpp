#include "commands.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "polygon.hpp"

void area(const std::vector<ayupov::Polygon>& polygon, std::istream& in, std::ostream& out)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return;
  }
  out << std::setprecision(1) << std::fixed;
  std::string mod = "";
  in >> mod;
  std::vector<ayupov::Polygon> polygonTC; //TC = toCount
  if (mod == "EVEN")
  {

  }
  else if (mod == "ODD")
  {

  }
  else if (mod == "MEAN")
  {

  }
  else
  {

  }
}
