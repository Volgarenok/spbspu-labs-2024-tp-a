#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <map>

namespace grechishnikov
{
  namespace detail
  {
    struct Node
    {
      std::map< std::string, Node >::iterator where_;
      std::string translation_;
      std::string definition_;

      Node();
      Node(std::map< std::string, Node >::iterator where);
      Node(const std::string& translation);
      Node(const std::string& translation, const std::string& definition);
    };
  }
}

#endif
