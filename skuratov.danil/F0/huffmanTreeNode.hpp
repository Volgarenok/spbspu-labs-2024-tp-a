#ifndef HUFFMANTREENODE_HPP
#define HUFFMANTREENODE_HPP

#include <cstddef>

namespace skuratov
{
  struct HuffmanTreeNode
  {
    char data;
    size_t freq;
    HuffmanTreeNode* left, * right;

    HuffmanTreeNode(char data, size_t freq)
    {
      left = right = nullptr;
      this->data = data;
      this->freq = freq;
    }
  };

  struct Compare
  {
    bool operator()(HuffmanTreeNode* l, HuffmanTreeNode* r)
    {
      return (l->freq > r->freq);
    }
  };
}

#endif
