#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace zagrivnyy
{
  struct Position
  {
    int row, col;
  };

  class Dictionary
  {
  public:
    Dictionary();

    bool add(std::string word, Position pos);

  private:
    std::unordered_map< std::string, std::vector< Position > > dict_;
  };
}
#endif
