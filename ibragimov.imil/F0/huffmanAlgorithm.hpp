#ifndef HUFFMAN_ALGORITHM_HPP
#define HUFFMAN_ALGORITHM_HPP

#include <map>
#include <memory>
#include <string>
#include "huffmanNode.hpp"

namespace ibragimov
{
  void encode(const std::string&);
  void decode();

  std::multimap< size_t, char > createFrequencyTable(const std::string&);
  std::unique_ptr< ibragimov::Node > createHuffmanTree(const std::multimap< size_t, char >&);
  std::map< char, size_t > createEncodingTable(std::unique_ptr< ibragimov::Node >);
}

#endif
