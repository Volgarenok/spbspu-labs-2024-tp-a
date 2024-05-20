#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include "word.hpp"

namespace nikitov
{
  class Dictionary
  {
    std::map< std::string, detail::Word > data_;
  };
}
#endif