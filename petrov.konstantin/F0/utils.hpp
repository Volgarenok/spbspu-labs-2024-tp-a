#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <memory>
#include <set>
#include <functional>
#include <iostream>

namespace petrov
{
  using shared_ptr = std::shared_ptr< char >;
  struct Node
  {
    char symbol;
    size_t freq;
    std::string code;
    shared_ptr left;
    shared_ptr right;

    using cRSP = const petrov::shared_ptr&;
    using str = std::string;
    Node(char nSym, size_t nFreq, str nCode, cRSP lhs, cRSP rhs);
    Node(const Node&) = default;
    Node(Node&&) = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;
  };
  std::ostream& operator<<(std::ostream& out, const Node& node);

  bool compareNodes(const Node& lhs, const Node& rhs);
  bool doesNodeHaveKey(const Node& node, char key);

  using cmpType = std::function< bool(const Node&, const Node&) >;
  using setType = std::set< Node, cmpType >;
  void addToSet(setType& alph, char symbol);

  void fillCodes(setType& alph);
}

#endif
