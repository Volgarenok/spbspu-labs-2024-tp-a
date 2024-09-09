#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <map>
#include <string>

namespace kozlov
{
  void doCmdHelp(std::ostream& out);
  void doCmdCreate(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdPrint(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdDelete(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdAdd(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdRemove(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdCount(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdSave(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdLoad(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
  void doCmdMerge(std::map< std::string, std::map< std::string, size_t > >& dicts, std::istream& in, std::ostream& out);
}
#endif
