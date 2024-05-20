#ifndef NODE_HPP
#define NODE_HPP
#include <cstddef>

namespace ravinskij
{
  struct Node
  {
    size_t frequency;
    char symbol;
    Node *left, *right;

    Node() = default;
    Node(const Node &) = default;
    Node(Node &&) = default;
    Node &operator=(const Node &) = default;
    Node &operator=(Node &&) = default;

    Node(Node *leftNode, Node *rightNode);
  };

  struct NodeComparator
  {
    bool operator()(const Node* lhs, const Node* rhs) const;
  };
}

#endif
