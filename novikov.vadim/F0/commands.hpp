#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <set>
#include <map>

namespace novikov
{
  using Dictionary = std::map< std::string, std::set< std::string > >;

  void insert();
  void search();
  void searchKeys();
  void searchValues();
  void remove();
  void removeKeys();
  void removeValues();

  void open();
  void save();
  void close();
  void print();
  void printReflected();
  void size();

  void merge();
  void intersect();
  void filter();
  void invert();
}

#endif
