#include "huffmanNode.hpp"

ibragimov::Node::Node(const char key, const size_t value):
  pair(std::pair< char, size_t >{key, value}),
  left(nullptr),
  right(nullptr)
{}
ibragimov::Node::Node(const std::pair< char, size_t >& pair):
  pair(pair),
  left(nullptr),
  right(nullptr)
{}
ibragimov::Node::Node(const char key, const size_t value, std::unique_ptr< Node >& l, std::unique_ptr< Node >& r):
  pair(std::pair< char, size_t >{key, value}),
  left(std::move(l)),
  right(std::move(r))
{}
ibragimov::Node::Node(const std::pair< char, size_t >& pair, std::unique_ptr< Node >& l, std::unique_ptr< Node >& r):
  pair(pair),
  left(std::move(l)),
  right(std::move(r))
{}
