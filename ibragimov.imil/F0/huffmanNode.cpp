#include "huffmanNode.hpp"

ibragimov::Node::Node(const std::pair< std::string, size_t >& pair):
  pair(pair),
  left(nullptr),
  right(nullptr)
{}
ibragimov::Node::Node(const std::pair< std::string, size_t >& pair, std::unique_ptr< Node >& l, std::unique_ptr< Node >& r):
  pair(pair),
  left(std::move(l)),
  right(std::move(r))
{}
