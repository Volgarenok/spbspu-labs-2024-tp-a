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
  void execCmdCreate(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdInsert(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdSelect(const std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdUpdate(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdAlter(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdDelete(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdClear(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdSave(const std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdClose(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdSort(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
  void execCmdLink(std::unordered_map< std::string, Table >& tables, std::istream& in, std::ostream& out);
}

int main()
{
  std::unordered_map< std::string, babinov::Table > tables;
  std::unordered_map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["tables"] = std::bind(babinov::execCmdTables, std::cref(tables), _2);
    cmds["load"] = std::bind(babinov::execCmdLoad, std::ref(tables), _1, _2);
    cmds["create"] = std::bind(babinov::execCmdCreate, std::ref(tables), _1, _2);
    cmds["insert"] = std::bind(babinov::execCmdInsert, std::ref(tables), _1, _2);
    cmds["select"] = std::bind(babinov::execCmdSelect, std::cref(tables), _1, _2);
    cmds["update"] = std::bind(babinov::execCmdUpdate, std::ref(tables), _1, _2);
    cmds["alter"] = std::bind(babinov::execCmdAlter, std::ref(tables), _1, _2);
    cmds["delete"] = std::bind(babinov::execCmdDelete, std::ref(tables), _1, _2);
    cmds["clear"] = std::bind(babinov::execCmdClear, std::ref(tables), _1, _2);
    cmds["save"] = std::bind(babinov::execCmdSave, std::cref(tables), _1, _2);
    cmds["close"] = std::bind(babinov::execCmdClose, std::ref(tables), _1, _2);
    cmds["sort"] = std::bind(babinov::execCmdSort, std::ref(tables), _1, _2);
    cmds["link"] = std::bind(babinov::execCmdLink, std::ref(tables), _1, _2);
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
