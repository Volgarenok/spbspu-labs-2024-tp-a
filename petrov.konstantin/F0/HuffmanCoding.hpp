#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include "utils.hpp"

namespace petrov
{
  class HuffmanTree
  {
    public:
    HuffmanTree(Node* node);
    void insert(Node& code);
    void merge(HuffmanTree& src);

    private:
    Node* root_;
  };
}

#endif
