#ifndef HUFFMAN_ALGORITHM_HPP
#define HUFFMAN_ALGORITHM_HPP

#include <map>
#include <string>

namespace ibragimov
{
  namespace detail
  {
    std::map< char, std::string > createEncodingTable(const std::string&);
    std::string encode(const std::string&, const std::map< char, std::string >&);
    std::string decode(const std::string&, const std::map< char, std::string >&);
  }
}

#endif
