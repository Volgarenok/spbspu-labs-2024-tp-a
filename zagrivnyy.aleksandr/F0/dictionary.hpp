#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace zagrivnyy
{
  struct Position
  {
    int row, col;
  };

  std::ostream &operator<<(std::ostream &out, const Position &pos);

  class Dictionary
  {
  public:
    Dictionary();

    void add(std::string word, Position pos);
    void add(std::string word, std::vector< Position > pos);
    void remove(std::string word);
    std::vector< Position > get(std::string word);

    std::unordered_map< std::string, std::vector< Position > > get_dict()
    {
      return dict_;
    }

  private:
    std::unordered_map< std::string, std::vector< Position > > dict_;
  };
}
#endif
