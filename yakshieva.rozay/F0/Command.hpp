#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include "dicts.hpp"

namespace yakshieva
{
  void newTree(std::string, tree_t&);
  void create(std::string commands, tree_t& dicts);
  void print(std::string commands, tree_t& dicts, std::ostream& out);
  void displayText(std::string commands, tree_t& dicts, std::ostream& out);
  void showLine(std::string commands, tree_t& dicts, std::ostream& out);
  void search(std::string commands, tree_t& dicts, std::ostream& out);
  void addLine(std::string commands, tree_t& dicts);
  void addWord(std::string commands, tree_t& dicts);
  void erase(std::string commands, tree_t& dicts);
  void remove(std::string commands, tree_t& dicts);
  void clear(std::string commands, tree_t& dicts);
}

#endif
