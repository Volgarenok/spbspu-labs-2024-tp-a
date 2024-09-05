#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include "huffmanTreeNode.hpp"
#include <queue>
#include <vector>

namespace skuratov
{
  void storeCodes(HuffmanTreeNode* root, const std::string& str, std::map< char, std::string >& huffmanCodes);
  void createHuffmanCodes(const std::string& text, std::map< char, std::string >& huffmanCodes);
  bool compressText(const std::string& text, const std::map< char, std::string >& huffmanCodes, std::string& encodedText);
  bool decompressText(const std::string& encodedText, const std::map< char, std::string >& huffmanCodes, std::string& decodedText);
  double calculateEfficiency(const std::string& text, const std::map< char, std::string >& huffmanCodes);
}

#endif
