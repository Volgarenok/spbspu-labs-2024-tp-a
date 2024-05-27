#include "commands.hpp"

#include <map>
#include <functional>
#include <string>

void gladyshev::findAreas(std::istream& in, const std::vector< Polygon > polys)
{
  std::map < std::string, std::function < double(const std::vector< Polygon >&) > > cmds;
  std::string command = "";
  double sum = 0;
  cmds["EVEN"] = findEven;
  cmds["ODD"] = findOdd;
  cmds["MEAN"] = findMean;
  in >> command;
  try
  {
    sum = cmds.at(command)(polys);
  }
  catch
  {
    size_t num = std::stoull(command);
    sum = findAreaCount(polys, num);
  }
  std::cout << sum;
}
void gladyshev::findMax(std::istream& in, const std::vector< Polygon > polys)
{

}
void gladdyshev::findMin(std::istream& in, const std::vector< Polygon > polys)
{

}
void gladdyshev::processCount(std::istream& in, const std::vector< Polygon > polys)
{

}
void gladyshev::findLessArea(std::istream& in, const std::vector< Polygon > polys)
{

}
void gladyshev::processEcho(std::istream& in, const std::vector< Polygon > polys);
{

}
double gladyshev::findEven(const std::vector< Polygon >& polys)
{

}
double gladyshev::findOdd(const std::vector< Polygon >& polys)
{

}
double gladyshev::findMean(const std::vector< Polygon >& polys)
{

}
double gladyshev::findAreaCount(const std::vector< Polygon >& polys, size_t n)
{

}
