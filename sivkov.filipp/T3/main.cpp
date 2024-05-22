#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>
#include <fstream>
#include <string>
#include <iterator>
#include "polygon.hpp"


namespace sivkov
{
  bool isEvenVertices(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOddVertices(const Polygon& polygon)
  {
    return polygon.points.size() % 2 != 0;
  }

  bool hasVertexCount(const Polygon& polygon, size_t count)
  {
    return polygon.points.size() == count;
  }


  /*
  void area(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    std::string arg = "";
    double areaSum = 0;
    if (arg == "EVEN")
    {

    }
    else if (arg == "ODD")
    {

    }
    else if (arg == "MEAN")
    {

    }
    else
    {

    }
  }
  */
  //void minMax(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
  void count(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons)
  {
    std::string arg = "";
    in >> arg;
    size_t count = 0;
    if (arg == "EVEN")
    {
      count = std::count_if(polygons.cbegin(), polygons.cend(), isEvenVertices);
    }
    else if (arg == "ODD")
    {
      count = std::count_if(polygons.cbegin(), polygons.cend(), isOddVertices);
    }
    else
    {
      long long ver = 0;
      try
      {
        ver = std::stoull(arg);
      }
      catch(const std::invalid_argument&)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      catch (const std::out_of_range&)
      {
        throw std::logic_error("<INVALID COMMAND>");
      }
      auto hasVertexCountBind = std::bind(hasVertexCount, std::placeholders::_1, ver);
      count = std::count_if(polygons.cbegin(), polygons.cend(), hasVertexCountBind);
    }
    out << count << "\n";
  }
  //void perms(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
  //void inframe(std::istream& in, std::ostream& out, const std::vector< Polygon >& polygons);
}


int main(int argc, char* argv[])
{
  using namespace sivkov;
  if (argc != 2)
  {
    std::cerr << "error cmd\n";
    return 1;
  }

  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "error file\n";
    return 1;
  }

  std::vector< Polygon > polygons;

  using input_iter = std::istream_iterator< Polygon >;

  while (!in.eof())
  {
    std::copy(input_iter{ in }, input_iter{}, std::back_inserter(polygons));
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::string arg = "";
  while (std::cin >> arg)
  {
    try
    {
      if (arg == "COUNT")
      {
        count(std::cin, std::cout, polygons);
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;

}
