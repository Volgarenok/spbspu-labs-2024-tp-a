#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <vector>
#include "polygonActions.hpp"

int main(int argc, char* argv[])
{
  if (argc < 2)
  {
    std::cerr << "Error: invalid args\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Error: cannot open file\n";
    return 2;
  }

  std::vector< spiridonov::Polygon > polygons;
  using input = std::istream_iterator< spiridonov::Polygon >;

  while (!file.eof())
  {
    std::copy(input{ file }, input{}, std::back_inserter(polygons));
    file.clear();
    file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  std::map< std::string, std::function< void(spiridonov::ActionStreams) > > actions;
  {
    using namespace std::placeholders;
    actions["AREA"] = std::bind(spiridonov::areaAction, std::cref(polygons), _1);
    actions["MIN"] = std::bind(spiridonov::minMaxAction, std::cref(polygons), _1, true);
    actions["MAX"] = std::bind(spiridonov::minMaxAction, std::cref(polygons), _1, false);
    actions["COUNT"] = std::bind(spiridonov::countAction, std::cref(polygons), _1);
    actions["ECHO"] = std::bind(spiridonov::echoAction, std::ref(polygons), _1);
    actions["LESSAREA"] = std::bind(spiridonov::lessAreaAction, std::ref(polygons), _1);
  }

  std::string action;
  while (std::cin >> action)
  {
    try
    {
      actions.at(action)(spiridonov::ActionStreams{ std::cin, std::cout });
      std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const spiridonov::InvalidActionException& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  file.close();
  return 0;
}
