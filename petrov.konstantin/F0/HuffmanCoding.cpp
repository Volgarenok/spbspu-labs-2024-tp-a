#include "HuffmanCoding.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <functional>
#include <numeric>
#include "utils.hpp"

std::ostream& petrov::decode(const setType& codes, std::ostream& dest, std::istream& src)
{
  src >> std::noskipws;
  std::string binary = "";
  std::string tmp;
  char ch;
  while (src >> ch)
  {
    binary += ch;
    auto dNHCode = std::bind(&doesNodeHaveCode, std::placeholders::_1, binary);
    auto symbolIt = std::find_if(codes.cbegin(), codes.cend(), dNHCode);
    if (symbolIt != codes.cend())
    {
      tmp += symbolIt->symbol;
      binary = "";
    }
  }
  if (binary != "")
  {
    throw std::logic_error("<NOT ENOUGH CODES>");
  }
  return dest << tmp;
}
std::ostream& petrov::encode(const setType& codes, std::ostream& dest, std::istream& src)
{
  src >> std::noskipws;
  using isIt = std::istream_iterator< char >;
  std::string text = "";
  auto coder = std::bind(&accCodes, codes, std::placeholders::_1, std::placeholders::_2);
  text = std::accumulate(isIt(src), isIt(), text, coder);
  src >> std::skipws;
  return dest << text;
}
petrov::setType& petrov::autoCodes(setType& dest, std::istream& in)
{
  in >> std::noskipws;
  using isIt = std::istream_iterator< char >;
  auto addToDest = std::bind(&addToSet, std::ref(dest), std::placeholders::_1);
  std::for_each(isIt(in), isIt(), addToDest);
  in >> std::skipws;
  return fillCodes(dest);
}

std::string petrov::accCodes(const setType& codes, const std::string& str, char chr)
{
  return str + encodeSymbol(codes, chr);
}
std::string petrov::encodeSymbol(const setType& codes, char src)
{
  auto dNHKey = std::bind(&doesNodeHaveKey, std::placeholders::_1, src);
  auto codeIt = std::find_if(codes.cbegin(), codes.cend(), dNHKey);
  return codeIt->code;
}
std::string petrov::getCode(Node::cRP root, char symbol, std::string code = "")
{
  if (!root)
  {
    return "";
  }
  if (root->symbol == symbol)
  {
    return code;
  }
  return getCode(root->left, symbol, code + '1') + getCode(root->right, symbol, code + '0');
}
petrov::setType& petrov::fillSetWithCodes(setType& dest, Node::cRP root)
{
  return fillSetWithCodes(dest, root, root);
}
petrov::setType& petrov::fillSetWithCodes(setType& dest, Node::cRP root, Node::cRP current)
{
  if (current)
  {
    if (current->symbol)
    {
      Node nodeWithCode(current->symbol, current->freq);
      nodeWithCode.code = getCode(root, current->symbol);
      dest.insert(nodeWithCode);
    }
    fillSetWithCodes(dest, root, current->left);
    fillSetWithCodes(dest, root, current->right);
  }
  return dest;
}
petrov::setType& petrov::fillCodes(setType& alph)
{
  setType codeTree(alph);
  std::vector< Node > tmpVector;
  std::copy(codeTree.cbegin(), codeTree.cend(), std::back_inserter(tmpVector));
  while (codeTree.size() > 1)
  {
    auto tmpIt = codeTree.begin();
    auto firstIt = tmpIt;
    auto secondIt = ++tmpIt;
    size_t newFreq = firstIt->freq + secondIt->freq;
    Node newNode(0, newFreq, "");
    auto dPHKFirst = std::bind(&isEqual, std::placeholders::_1, *firstIt);
    newNode.left = std::make_shared< Node >(*std::find_if(tmpVector.begin(), tmpVector.end(), dPHKFirst));
    auto dPHKSecond = std::bind(&isEqual, std::placeholders::_1, *secondIt);
    newNode.right = std::make_shared< Node >(*std::find_if(tmpVector.begin(), tmpVector.end(), dPHKSecond));
    tmpVector.push_back(newNode);

    codeTree.erase(firstIt);
    codeTree.erase(secondIt);
    codeTree.insert(newNode);
  }
  setType newAlph(compareNodes);
  auto root = codeTree.begin();
  alph.swap(fillSetWithCodes(newAlph, std::make_shared< Node >(*root)));

  return alph;
}
