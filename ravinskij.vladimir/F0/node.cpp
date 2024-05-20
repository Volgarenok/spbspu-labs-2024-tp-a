#include "node.hpp"

namespace rav = ravinskij;
rav::Node::Node(Node *leftNode, Node *rightNode):
  frequency(0),
  symbol(0),
  left(leftNode),
  right(rightNode)
{
  frequency = leftNode->frequency + rightNode->frequency;
}

bool rav::NodeComparator::operator()(const Node *lhs, const Node *rhs) const
{
  return lhs->frequency < rhs->frequency;
}
