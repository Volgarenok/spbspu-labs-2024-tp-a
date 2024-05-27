#ifndef HUFFMAN_TREE_NODE_HPP
#define HUFFMAN_TREE_NODE_HPP

#include <cstddef>

namespace skuratov
{
  class HuffmanTreeNode
  {
  public:
    size_t a = {};
    char c = {};
    HuffmanTreeNode* left;
    HuffmanTreeNode* right;

    HuffmanTreeNode()
    {
      left = nullptr;
      right = nullptr;
    }

    HuffmanTreeNode(HuffmanTreeNode* L, HuffmanTreeNode* R)
    {
      left = L;
      right = R;
      a = L->a + R->a;
    }
  };
}

#endif
