#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <memory>
#include <set>
#include <functional>
#include <iostream>

namespace petrov
{
  struct Node
  {
    using ptr = std::shared_ptr< Node >;
    using cRP = const ptr&;

    char symbol;
    size_t freq;
    std::string code;
    ptr left;
    ptr right;

    using str = std::string;
    Node(char nSym = 0, size_t nFreq = 1, str nCode = "");
    Node(const Node&) = default;
    Node(Node&&) = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;
  };
  using ptr = std::shared_ptr< Node >;
  std::ostream& operator<<(std::ostream& out, const Node& node);
  std::istream& operator>>(std::istream& in, Node& node);

  bool compareNodes(const Node& lhs, const Node& rhs);
  bool doesNodeHaveKey(const Node& node, char key);
  bool doesNodeHaveCode(const Node& node, const std::string& code);
  bool isEqual(const Node& n1, const Node& n2);

  using cmpType = std::function< bool(const Node&, const Node&) >;
  using setType = std::set< Node, cmpType >;
  void addToSet(setType& alph, char symbol);
  bool doesContain(const setType& set, const Node& node);
  bool isSubset(const setType& mainSet, const setType& testedSet);
}

#endif
