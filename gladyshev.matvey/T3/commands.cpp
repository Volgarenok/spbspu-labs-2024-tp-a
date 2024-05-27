#include "commands.hpp"

#include <map>
#include <functional>
#include <string>
#include <iostream>
#include <algorithm>

void gladyshev::findAreas(std::istream& in, const std::vector< Polygon >& polys)
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

void gladyshev::findMax(std::istream& in, const std::vector< Polygon >& polys)
{
  std::string command = "";
  in >> command;
  if (command == "AREA")
  {
    auto cmp = [](const Polygon& left, const Polygon& right)
      {
        return findArea(left) > findArea(right);
      };
    auto maxArea = std::min_element(polys.begin(), polys.end(), cmp);
    std::cout << findArea(*maxArea);
  }
  else
  {
     auto cmp = [](const Polygon& left, const Polygon& right)
      {
        return left.points.size() > right.points.size();
      };
     auto maxPnt = std::min_element(polys.begin(), polys.end(), cmp);
     std::cout << maxPnt->points.size();
  }
}
void gladyshev::findMin(std::istream& in, const std::vector< Polygon >& polys)
{
  std::string command = "";
  in >> command;
  if (command == "AREA")
  {
    auto cmp = [](const Polygon& left, const Polygon& right)
      {
        return findArea(left) < findArea(right);
      };
    auto minArea = std::min_element(polys.cbegin(), polys.cend(), cmp);
    std::cout << findArea(*minArea);
  }
  else
  {
     auto cmp = [](const Polygon& left, const Polygon& right)
      {
        return left.points.size() < right.points.size();
      };
     auto minPnt = std::min_element(polys.cbegin(), polys.cend(), cmp);
     std::cout << minPnt->points.size();
  }
}
void gladyshev::processCount(std::istream& in, const std::vector< Polygon >& polys)
{
  std::map < std::string, std::function < size_t(const std::vector< Polygon >&) > > cmds;
  std::string command = "";
  size_t num = 0;
  cmds["EVEN"] = countEven;
  cmds["ODD"] = countOdd;
  in >> command;
  try
  {
    num = cmds.at(command)(polys);
  }
  catch
  {
    size_t verts = std::stoull(command);
    num = countVerts(polys, verts);
  }
}
void gladyshev::findLessArea(std::istream& in, const std::vector< Polygon >& polys)
{

}
void gladyshev::processEcho(std::istream& in, const std::vector< Polygon >& polys);
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

size_t gladyshev::countEven(const std::vector< Polygon >& polys)
{

}

size_t gladyshev::countOdd(const std::vector< Polygon >& polys)
{

}
