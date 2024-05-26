#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

#include <memory>
#include <string>

namespace ibragimov
{
  struct Node
  {
    Node() = default;
    Node(const std::pair< std::string, size_t >&);
    Node(const std::pair< std::string, size_t >&, std::unique_ptr< Node >&, std::unique_ptr< Node >&);
    Node(const Node&) = delete;
    ~Node() = default;

    std::pair< std::string, size_t > pair;
    std::unique_ptr< Node > left;
    std::unique_ptr< Node > right;
  };
}

#endif
