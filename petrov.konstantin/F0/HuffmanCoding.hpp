#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include <iostream>
#include <string>
#include <map>
#include "utils.hpp"

namespace petrov
{
  using mapType = std::map< std::string, std::string >;
  class HuffmanCoding
  {
    public:
    mapType& readText(mapType& texts, std::string& text, const std::string& name);
    void writeText(mapType& texts, const std::string& name, const std::string& text);
    std::ostream& decode(const setType& codes, std::ostream& dest, std::istream& src);
    std::ostream& encode(const setType& codes, std::ostream& dest, std::istream& src);
    setType& autoCodes(setType& dest, std::istream& in);

    private:
    std::string accCodes(const setType& codes, const std::string& str, char chr);
    std::string encodeSymbol(const setType& codes, char src);
    std::string getCode(Node::cRP root, char symbol, std::string code);
    setType& fillSetWithCodes(setType& dest, Node::cRP root);
    setType& fillSetWithCodes(setType& dest, Node::cRP root, Node::cRP current);
    setType& fillCodes(setType& alph);
  };
}

#endif
