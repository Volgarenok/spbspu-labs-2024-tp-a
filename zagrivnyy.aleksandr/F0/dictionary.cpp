#include "dictionary.hpp"

zagrivnyy::Dictionary::Dictionary():
  dict_()
{
}

bool zagrivnyy::Dictionary::add(std::string word, zagrivnyy::Position pos)
{
  auto it = dict_.find(word);
  if (it != dict_.end())
  {
    it->second.push_back(pos);
  }
  else
  {
    std::vector< zagrivnyy::Position > positions = {pos};
    dict_.insert(std::make_pair(word, positions));
  }

  return true;
}
