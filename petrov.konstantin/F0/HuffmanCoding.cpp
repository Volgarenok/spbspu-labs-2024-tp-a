#include "HuffmanCoding.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <functional>
#include <numeric>
#include "utils.hpp"

void petrov::HuffmanCoding::readText(const std::string& text, const std::string& name)
{
  if (texts_.find(name) != texts_.cend())
  {
    std::cout << "This name is taken. Read anyway y/n: ";
    char ans;
    std::cin >> ans;
    if (ans == 'y')
    {
      texts_[name] = text;
    }
  }
}
std::ostream& petrov::HuffmanCoding::decode(const setType& codes, std::ostream& dest, std::istream& src)
{
  src >> std::noskipws;
  std::string binary = "";
  while (!src.eof())
  {
    char chr;
    src >> chr;
    binary += chr;
    auto dNHCode = std::bind(&doesNodeHaveCode, std::placeholders::_1, binary);
    auto symbolIt = std::find_if(codes.cbegin(), codes.cend(), dNHCode);
    if (symbolIt != codes.cend())
    {
      dest << symbolIt->symbol;
      binary = "";
    }
  }
  return dest;
}
std::ostream& petrov::HuffmanCoding::encode(const setType& codes, std::ostream& dest, std::istream& src)
{
  src >> std::noskipws;
  using isIt = std::istream_iterator< char >;
  std::string text = "";
  auto coder = std::bind(&accCodes, this, codes, std::placeholders::_1, std::placeholders::_2);
  text = std::accumulate(isIt(src), isIt(), text, coder);
  src >> std::skipws;
  return dest << text;
}
petrov::setType& petrov::HuffmanCoding::autoCodes(setType& dest, std::istream& in)
{
  in >> std::noskipws;
  using isIt = std::istream_iterator< char >;
  auto addToDest = std::bind(&addToSet, std::ref(dest), std::placeholders::_1);
  std::for_each(isIt(in), isIt(), addToDest);
  in >> std::skipws;
  return fillCodes(dest);
}

std::string petrov::HuffmanCoding::accCodes(const setType& codes, const std::string& str, char chr)
{
  return str + encodeSymbol(codes, chr);
}
std::string petrov::HuffmanCoding::encodeSymbol(const setType& codes, char src)
{
  auto dNHKey = std::bind(&doesNodeHaveKey, std::placeholders::_1, src);
  auto codeIt = std::find_if(codes.cbegin(), codes.cend(), dNHKey);
  return codeIt->code;
}
std::string petrov::HuffmanCoding::getCode(Node::cRP root, char symbol, std::string code = "")
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
petrov::setType& petrov::HuffmanCoding::fillSetWithCodes(setType& dest, Node::cRP root)
{
  return fillSetWithCodes(dest, root, root);
}
petrov::setType& petrov::HuffmanCoding::fillSetWithCodes(setType& dest, Node::cRP root, Node::cRP current)
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
petrov::setType& petrov::HuffmanCoding::fillCodes(setType& alph)
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
