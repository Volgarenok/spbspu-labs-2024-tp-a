#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include "freqList.hpp"

namespace isaychev
{
  void make_freqlist(std::istream & in, std::map< std::string, FreqList > & col);
  /*void delete_freqlist();
  void merge();
  void print();
  void print_last();
  void print_first();
  void get_context();
  void count();
  void get_total();
  void get_unique();
  void sort();*/
}

#endif
