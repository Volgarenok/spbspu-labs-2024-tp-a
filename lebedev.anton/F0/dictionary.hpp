#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <map>
#include <string>

namespace lebedev
{
  class Dictionary
  {
  public:
    void recordWord(const std::string & word, const size_t & n = 1);
    std::map< std::string, size_t > getDict() const;
  private:
    std::map< std::string, size_t > dict_;
  };
  std::istream & operator>>(std::istream & input, Dictionary & dict);
}

#endif
