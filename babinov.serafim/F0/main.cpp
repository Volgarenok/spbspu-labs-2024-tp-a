#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include "table.hpp"

namespace babinov
{
  void execCmdTables(const std::unordered_map< std::string, Table >& tables, std::ostream& out);
  void execCmdLoad(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
}

int main()
{
  std::unordered_map< std::string, babinov::Table > tables;
  std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["tables"] = std::bind(babinov::execCmdTables, std::cref(tables), _2);
    cmds["load"] = std::bind(babinov::execCmdLoad, std::ref(tables), _1, _2);
  }
  std::string cmd;
  std::cout << "==$ ";

  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    std::cout << "==$ ";
  }
  return 0;
}
