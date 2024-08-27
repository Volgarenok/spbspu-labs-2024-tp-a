#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include "freqList.hpp"

namespace isaychev
{
  using collection_t = std::map< std::string, FreqList >;

  void make_freqlist(collection_t & col, std::istream & in);
  void delete_freqlist(collection_t & col, std::istream & in);
  void print(const collection_t & col, std::istream & in, std::ostream & out);
  void count(const collection_t & col, std::istream & in, std::ostream & out);
  void get_total(const collection_t & col, std::istream & in, std::ostream & out);
  void get_unique(const collection_t & col, std::istream & in, std::ostream & out);
  void print_first(const collection_t & col, std::istream & in, std::ostream & out);
  void print_last(const collection_t & col, std::istream & in, std::ostream & out);
  void merge(collection_t & col, std::istream & in);
  void print_descending(const collection_t & col, std::istream & in, std::ostream & out);
  /*
  void get_context();
  void sort();*/
}

#endif
