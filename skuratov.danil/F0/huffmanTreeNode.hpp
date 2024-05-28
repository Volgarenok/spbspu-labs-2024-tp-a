#ifndef HUFFMANTREENODE_HPP
#define HUFFMANTREENODE_HPP

#include <cstddef>
#include <map>
#include <string>

namespace skuratov
{
  struct HuffmanTreeNode
  {
    char data;
    size_t freq;
    HuffmanTreeNode* left;
    HuffmanTreeNode* right;

    HuffmanTreeNode(char data, size_t freq):
      data(data),
      freq(freq),
      left(nullptr),
      right(nullptr)
    {}
  };

  struct Compare
  {
    bool operator()(HuffmanTreeNode* l, HuffmanTreeNode* r)
    {
      return (l->freq > r->freq);
    }
  };

  struct Context
  {
    std::map< std::string, std::string > context;
  };

  struct CodeContext
  {
    std::map< std::string, std::map< char, std::string > > codeContext;
  };
}

#endif
