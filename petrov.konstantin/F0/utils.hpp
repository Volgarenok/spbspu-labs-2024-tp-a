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
    size_t freq;
    char symbol;
    shared_ptr left;
    shared_ptr right;

    Node(char sym);
    Node(const Node&) = default;
    Node(Node&&) = default;
    Node& operator=(const Node&) = default;
    Node& operator=(Node&&) = default;

    Node(const shared_ptr& lhs, const shared_ptr& rhs);
  };
  std::ostream& operator<<(std::ostream& out, const Node& node);

  bool compareNodes(const Node& lhs, const Node& rhs);
  bool doesNodeHaveKey(const Node& node, char key);

  using pairType = std::pair< Node, int >;
  bool comparePairs(const pairType& lhs, const pairType& rhs);
  bool doesPairHaveKey(const pairType& pair, char key);
  std::ostream& operator<<(std::ostream& out, pairType pair);

  using cmpType = std::function< bool(const pairType&, const pairType&) >;
  using setType = std::set< pairType, cmpType >;
  void addToSet(setType& alph, char symbol);
}

#endif
