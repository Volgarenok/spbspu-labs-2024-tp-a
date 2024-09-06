#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include <string>
#include <iostream>

namespace zhakha
{
  struct Dictionary
  {
    std::map<std::string, size_t> dic;
  };

  std::istream& operator>>(std::istream& in, Dictionary& dic);
  std::ostream& operator<<(std::ostream& out, const Dictionary& dic);

  struct Node
  {
    Node();
    Node(const std::pair<std::string, size_t>& pr);
    std::pair<std::string, size_t> pair;

  };

  std::istream& operator>>(std::istream& in, Node& node);
  std::ostream& operator<<(std::ostream& out, const Node& node);
  std::pair<std::string, size_t> getNode(const Node&);
  Node getVal(const std::pair<std::string, size_t>& node);

}

#endif
