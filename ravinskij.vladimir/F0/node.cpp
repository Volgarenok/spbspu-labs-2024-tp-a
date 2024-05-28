#include "node.hpp"

namespace rav = ravinskij;

rav::Node::Node(size_t freq, char symb):
  frequency(freq),
  symbol(symb),
  left(nullptr),
  right(nullptr)
{}

rav::Node::Node(const nodePtr& leftNode, const nodePtr& rightNode):
  frequency(0),
  symbol(0),
  left(leftNode),
  right(rightNode)
{
  frequency = leftNode->frequency + rightNode->frequency;
}

bool rav::NodeComparator::operator()(const nodePtr& lhs, const nodePtr& rhs) const
{
  return lhs->frequency < rhs->frequency;
}
