#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace timchishina
{
  void doHelp(std::ostream& out);
  void doCreate(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doDelete(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doPrint(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doAdd(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doRemove(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doAddLine(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doRemoveLine(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doRemoveColumn(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doFind(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doSave(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
  void doLoad(std::map< std::string, std::map< std::string, std::map< int, std::vector< int > > > >& dicts, std::istream& in, std::ostream& out);
}
#endif
