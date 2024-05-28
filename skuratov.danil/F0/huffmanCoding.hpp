#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include "huffmanTreeNode.hpp"
#include <unordered_map>
#include <string>

namespace skuratov
{
	void createHuffmanCodes(const std::string& text, std::unordered_map< char, std::string >& huffmanCodes);
	bool compressText(const std::string& text, const std::unordered_map< char, std::string >& huffmanCodes, std::string& encodedText);
	bool decompressText(const std::string& encodedText, const std::unordered_map< char, std::string >& huffmanCodes, std::string& decodedText);
	double calculateEfficiency(const std::string& text, const std::unordered_map< char, std::string>& huffmanCodes);
}

#endif
