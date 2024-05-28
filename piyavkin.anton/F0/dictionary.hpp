#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP
#include <istream>
#include <map>

namespace piyavkin
{
  struct Node
  {
    std::pair< std::string, size_t > pair;
  };
  std::istream& operator>>(std::istream& in, Node& node);
  std::pair< std::string, size_t > getNode(const Node&);
  struct Dictionary
  {
    std::map< std::string, size_t > dic;
  };
  std::istream& operator>>(std::istream& in, Dictionary& dic);
}
#endif