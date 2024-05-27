#ifndef HUFFMAN_CODING_HPP
#define HUFFMAN_CODING_HPP

#include "utils.hpp"
#include <iostream>
#include <string>

namespace petrov
{
  class HuffmanCoding
  {
    public:
    setType& autoCodes(setType& dest, std::istream& in);

    private:
    std::string getCode(Node::cRP root, char symbol, std::string code);
    setType& fillSetWithCodes(setType& dest, Node::cRP root);
    setType& fillSetWithCodes(setType& dest, Node::cRP root, Node::cRP current);
    setType& fillCodes(setType& alph);
  };
}

#endif
