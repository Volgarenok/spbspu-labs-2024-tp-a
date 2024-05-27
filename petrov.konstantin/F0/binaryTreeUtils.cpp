#include "binaryTreeUtils.hpp"
#include "utils.hpp"

petrov::Node::ptr petrov::getMin(Node::cRP node)
{
  Node::ptr current = nullptr;
  if (node)
  {
    current = node;
    while (current->left)
    {
      current = current->left;
    }
  }
  return current;
}
petrov::Node::ptr petrov::getNext(Node::cRP node)
{
  if (node->right)
  {
    return getMin(node->right);
  }
  Node::ptr current = node;
  Node::ptr curParent = node->parent;
  while (curParent && (current == curParent->right))
  {
    current = curParent;
    curParent = curParent->parent;
  }
  return curParent;
}
