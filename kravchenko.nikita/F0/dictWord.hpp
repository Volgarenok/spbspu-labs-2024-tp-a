#ifndef DICT_WORD_HPP
#define DICT_WORD_HPP

#include <istream>
#include <string>

namespace kravchenko
{
  struct DictWord
  {
    std::string& word;
  };
  std::istream& operator>>(std::istream& in, DictWord&& word);
}

#endif
