#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include "freqList.hpp"

namespace isaychev
{
  void make_freqlist(std::istream & in, std::map< std::string, FreqList > & col);
  void delete_freqlist(std::istream & in, std::map< std::string, FreqList > & col);
  void print(std::istream & in, std::ostream & out, std::map< std::string, FreqList > & col);
  void count(std::istream & in, std::ostream & out, std::map< std::string, FreqList > & col);
  void get_total(std::istream & in, std::ostream & out, std::map< std::string, FreqList > & col);
  /*void merge();
  void print_last();
  void print_first();
  void get_context();
  void get_unique();
  void sort();*/
}

#endif
