#ifndef HUFFMAN_NODE_HPP
#define HUFFMAN_NODE_HPP

#include <memory>

namespace ibragimov
{
  namespace detail
  {
    struct Node
    {
      Node() = default;
      Node(const std::pair< size_t, char >&);
      Node(const size_t, std::unique_ptr< Node >&, std::unique_ptr< Node >&);
      Node(const Node&) = delete;
      ~Node() = default;

      std::pair< size_t, char > pair;
      std::unique_ptr< Node > left;
      std::unique_ptr< Node > right;
    };
  }
}

#endif
