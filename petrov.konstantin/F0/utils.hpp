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
    shared_ptr left;
    shared_ptr right;

    Node(char sym, size_t frequency);
    Node(const Node&) = default;
    Node(Node&&) = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;

    Node(const shared_ptr& lhs, const shared_ptr& rhs);
  };
  std::ostream& operator<<(std::ostream& out, const Node& node);

  bool compareNodes(const Node& lhs, const Node& rhs);
  bool doesNodeHaveKey(const Node& node, char key);

  using cmpType = std::function< bool(const Node&, const Node&) >;
  using setType = std::set< Node, cmpType >;
  void addToSet(setType& alph, char symbol);
}

#endif
