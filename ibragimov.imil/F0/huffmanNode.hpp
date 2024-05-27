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
      Node(const char, const size_t);
      Node(const std::pair< char, size_t >& pair);
      Node(const char, const size_t, std::unique_ptr< Node >&, std::unique_ptr< Node >&);
      Node(const std::pair< char, size_t >& pair, std::unique_ptr< Node >& l, std::unique_ptr< Node >& r);
      Node(const Node&) = delete;
      ~Node() = default;

      std::pair< char, size_t > pair;
      std::unique_ptr< Node > left;
      std::unique_ptr< Node > right;
    };
  }
}

#endif
