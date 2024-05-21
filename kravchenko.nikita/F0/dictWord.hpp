#ifndef DICT_WORD_HPP
#define DICT_WORD_HPP

#include <string>
#include <istream>

namespace kravchenko
{
  struct DictWord
  {
    std::string& word;
  }
  std::istream& operator>>(std::istream& in, DictWord&& word);
}

#ifndef