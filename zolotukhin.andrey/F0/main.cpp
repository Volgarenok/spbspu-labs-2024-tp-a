#include <iostream>
#include <iterator>
#include <algorithm>
#include <limits>
#include <fstream>
#include <map>
#include <functional>
#include <vector>

#include "commands.cpp"
#include "set.hpp"

int main(int argc, char* argv[])
{
  using namespace zolotukhin;
  std::map<std::string, Set> Sets;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["CREATE"] = std::bind(create, std::ref(Sets), _1, _2);
    cmds["ADD"] = std::bind(addWord, std::ref(Sets), _1, _2);
    cmds["SEARCH"] = std::bind(search, std::ref(Sets), _1, _2);
    cmds["CLEAR"] = std::bind(clearSet, std::ref(Sets), _1, _2);
    cmds["MERGE"] = std::bind(mergeSets, std::ref(Sets), _1, _2);
    cmds["INTERSECT"] = std::bind(intersectSets, std::ref(Sets), _1, _2);
    cmds["REMOVE"] = std::bind(removeWord, std::ref(Sets), _1, _2);
    cmds["DISPLAY"] = std::bind(display, std::ref(Sets), _1, _2);
    cmds["COUNT"] = std::bind(countWords, std::ref(Sets), _1, _2);
  }
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what();
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
