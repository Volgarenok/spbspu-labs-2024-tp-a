#include "node.hpp"

namespace grechishnikov
{
  detail::Node::Node():
    where_({ nullptr })
  {}

  detail::Node::Node(std::map< std::string, Node >::iterator where):
    where_(where)
  {}


  detail::Node::Node(const std::string& translation):
    where_({ nullptr }),
    translation_(translation)
  {}

  detail::Node::Node(const std::string& translation, const std::string& definition):
    where_({ nullptr }),
    translation_(translation),
    definition_(definition)
  {}
}
