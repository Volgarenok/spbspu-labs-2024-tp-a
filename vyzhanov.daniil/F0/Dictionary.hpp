#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <map>
#include <set>

namespace vyzhanov
{
  struct Dictionary
  {
    Dictionary();
    ~Dictionary();
  private:
    std::map< std::string, std::set< std::string > > dict_;
  };
}

#endif
