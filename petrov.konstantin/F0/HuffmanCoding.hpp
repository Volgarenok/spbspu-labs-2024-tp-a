#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include <iostream>
#include <string>
#include <map>
#include "utils.hpp"

namespace petrov
{
  class HuffmanCoding
  {
    public:
    void readText(const std::string& text, const std::string& name);
    std::ostream& decode(const setType& codes, std::ostream& dest, std::istream& src);
    std::ostream& encode(const setType& codes, std::ostream& dest, std::istream& src);
    setType& autoCodes(setType& dest, std::istream& in);

    private:
    std::map<std::string, std::string> texts_;

    std::string accCodes(const setType& codes, const std::string& str, char chr);
    std::string encodeSymbol(const setType& codes, char src);
    std::string getCode(Node::cRP root, char symbol, std::string code);
    setType& fillSetWithCodes(setType& dest, Node::cRP root);
    setType& fillSetWithCodes(setType& dest, Node::cRP root, Node::cRP current);
    setType& fillCodes(setType& alph);
  };
}

#endif
