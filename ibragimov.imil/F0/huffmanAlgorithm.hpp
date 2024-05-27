#ifndef HUFFMAN_ALGORITHM_HPP
#define HUFFMAN_ALGORITHM_HPP

#include <map>
#include <memory>
#include <string>
#include "huffmanNode.hpp"

namespace ibragimov
{
  std::map< char, std::string > createEncodingTable(const std::string&);
  std::string encode(const std::string&, const std::map< char, std::string >&);
  std::string decode(const std::string&, const std::map< char, std::string >&);

  std::multimap< size_t, char > createFrequencyTable(const std::string&);
  std::unique_ptr< ibragimov::Node > createHuffmanTree(const std::multimap< size_t, char >&);
  std::multimap< size_t, char > createCodesLengthTable(const std::unique_ptr< ibragimov::Node >&);
  std::map< char, std::string > createEncodingTable(const std::multimap< size_t, char >&);
}

#endif
