#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include "huffmanTreeNode.hpp"

namespace skuratov
{
  struct MyCompare
  {
    bool operator()(HuffmanTreeNode* l, HuffmanTreeNode* r) const
    {
      return l->a < r->a;
    }
  };

  std::vector< bool > code;
  std::map< char, std::vector< bool > > table;

  void buildAssociationTable(HuffmanTreeNode* root)
  {
    if (root->left != nullptr)
    {
      code.push_back(0);
      buildAssociationTable(root->left);
      code.pop_back();
    }

    if (root->right != nullptr)
    {
      code.push_back(1);
      buildAssociationTable(root->right);
      code.pop_back();
    }

    if (root->left == nullptr && root->right == nullptr)
    {
      table[root->c] = code;
    }
  }
}

#endif
