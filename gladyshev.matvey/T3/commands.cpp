#include "commands.hpp"

#include <iomanip>
#include <map>
#include <functional>
#include <iostream>

void gladyshev::findAreas(std::istream& in, std::ostream& out,  const std::vector< Polygon >& polys)
{
  std::string command = "";
  double sum = 0;
  in >> command;
  if (command == "MEAN")
  {
    if (polys.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    double t = (mainSum(polys, isEvenOdd) + mainSum(polys, std::not1(std::ptr_fun(isEvenOdd))));
    sum = t / polys.size();
  }
  else if (command == "ODD")
  {
    sum = mainSum(polys, std::not1(std::ptr_fun(isEvenOdd)));
  }
  else if (command == "EVEN")
  {
    sum = mainSum(polys, isEvenOdd);
  }
  else
  {
    size_t num = std::stoull(command);
    if (num < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    auto cmp = std::bind(checkVerts, std::placeholders::_1, num);
    sum = mainSum(polys, cmp);
  }
  out << std::fixed << std::setprecision(1) << sum << "\n";
}

void gladyshev::findMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  if (polys.empty())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  std::string command = "";
  in >> command;
  if (command == "AREA")
  {
    auto maxArea = std::max_element(polys.begin(), polys.end(), checkArea);
    out << std::fixed << std::setprecision(1) << findArea(*maxArea) << "\n";
  }
  else
  {
     auto maxPnt = std::max_element(polys.begin(), polys.end(), checkPoints);
     out << maxPnt->points.size() << "\n";
  }
}
void gladyshev::findMin(std::istream& in, std::ostream& out,  const std::vector< Polygon >& polys)
{
  std::string command = "";
  in >> command;
  if (command == "AREA")
  {
    auto minArea = std::min_element(polys.cbegin(), polys.cend(), checkArea);
    out << findArea(*minArea);
  }
  else
  {
    auto minPnt = std::min_element(polys.cbegin(), polys.cend(), checkPoints);
    out << minPnt->points.size();
  }
}
bool gladyshev::compareArea(const Polygon& left, const Polygon& right)
{
  return findArea(left) < findArea(right);
}
bool gladyshev::comparePoints(const Polygon& left, const Polygon& right)
{
  return left.points.size() < right.points.size();
}
void gladyshev::processEcho(std::istream& in, std::ostream& out, std::vector< Polygon >& polys)
{
  Polygon poly;
  in >> poly;
  if (!in || in.get() != '\n')
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  size_t num = std::count(polys.cbegin(), polys.cend(), poly);
  std::vector< Polygon > temp;
  std::transform(polys.begin(), polys.end(), std::back_inserter(temp), [&](Polygon pol)
  {
    if (pol == poly)
    {
      temp.push_back(pol);
    }
    return pol;
  });
  polys = temp;
  out << num << "\n";
}
void gladyshev::findLessArea(std::istream& in, std::ostream& out, const std::vector< Polygon >& polys)
{
  Polygon poly;
  in >> poly;
  if (!in || in.get() != '\n')
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto res = std::count_if(polys.cbegin(), polys.cend(), std::bind(checkArea, std::placeholders::_1, poly));
  out << res << "\n";
}
void gladyshev::processCount(std::istream& in, std::ostream& out,  const std::vector< Polygon >& polys)
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
  catch (...)
  {
    size_t verts = std::stoull(command);
    if (verts < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    num = countNum(polys, verts);
  }
  out << num << "\n";
}

bool gladyshev::isEvenOdd(const Polygon& poly)
{
  return poly.points.size() % 2 == 0;
}
bool gladyshev::checkVerts(const Polygon& poly, size_t n)
{
  return poly.points.size() == n;
}
size_t gladyshev::countEven(const std::vector< Polygon >& polys)
{
  return count_if(polys.cbegin(), polys.cend(), isEvenOdd);
}
size_t gladyshev::countOdd(const std::vector< Polygon >& polys)
{
  return count_if(polys.cbegin(), polys.cend(), std::not1(std::ptr_fun(isEvenOdd)));
}
size_t gladyshev::countNum(const std::vector< Polygon >& polys, size_t n)
{
  auto check = std::bind(checkVerts, std::placeholders::_1, n);
  return count_if(polys.cbegin(), polys.cend(), check);
}
