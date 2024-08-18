#ifndef NODE_HPP
#define NODE_HPP
#include <cstddef>
#include <memory>

namespace ravinskij
{
  struct Node;

  using nodePtr = std::shared_ptr< Node >;
  struct Node
  {
    size_t frequency;
    char symbol;
    nodePtr left, right;

    Node(size_t freq, char symb);
    Node(const nodePtr& leftNode, const nodePtr& rightNode);
  };

  struct NodeComparator
  {
    bool operator()(const nodePtr& lhs, const nodePtr& rhs) const;
  };
}

#endif
