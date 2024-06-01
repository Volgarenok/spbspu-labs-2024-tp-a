#include "huffmanNode.hpp"

ibragimov::detail::Node::Node(const std::pair< size_t, char >& pair):
  pair(pair),
  left(nullptr),
  right(nullptr)
{}
ibragimov::detail::Node::Node(const size_t key, std::unique_ptr< Node >& l, std::unique_ptr< Node >& r):
  pair(std::make_pair(key, ' ')),
  left(std::move(l)),
  right(std::move(r))
{}
