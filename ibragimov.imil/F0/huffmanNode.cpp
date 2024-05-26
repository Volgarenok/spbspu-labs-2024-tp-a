#include "huffmanNode.hpp"

ibragimov::Node::Node(const std::string& key, size_t value):
  pair(std::pair< std::string, size_t >{key, value}),
  left(nullptr),
  right(nullptr)
{}
ibragimov::Node::Node(const std::string& key, size_t value, std::unique_ptr< Node >& l, std::unique_ptr< Node >& r):
  pair(std::pair< std::string, size_t >{key, value}),
  left(std::move(l)),
  right(std::move(r))
{}
