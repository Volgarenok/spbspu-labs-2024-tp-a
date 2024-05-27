#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <functional>
#include <set>

#include <iostream>
#include <iterator>

#include "binaryTreeUtils.hpp"

petrov::Node::Node(char nSym = 0, size_t nFreq = 1, str nCode = ""):
  symbol(nSym),
  freq(nFreq),
  code(nCode)
{}
std::ostream& petrov::operator<<(std::ostream& out, const Node& node)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out.flush();
  return out << node.symbol << " : " << node.freq << " : " << node.code;
}
bool petrov::compareNodes(const Node& lhs, const Node& rhs)
{
  return lhs.freq <= rhs.freq && lhs.symbol != rhs.symbol;
}
bool petrov::doesNodeHaveKey(const Node& node, char key)
{
  return node.symbol == key;
}

void petrov::addToSet(setType& alph, char symbol)
{
  auto dPHKey = std::bind(&doesNodeHaveKey, std::placeholders::_1, symbol);
  auto element = std::find_if(alph.begin(), alph.end(), dPHKey);
  if (element != alph.end())
  {
    Node tmp = (*element);
    alph.erase(element);
    tmp.freq += 1;
    alph.insert(tmp);
  }
  else
  {
    alph.insert(Node(symbol));
  }
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
petrov::setType& petrov::fillSetWithCodes(setType& dest, const setType& codeTree)
{
  Node rootNode = *(codeTree.begin());
  ptr first = getMin(static_cast< Node::ptr >(&rootNode));
  while (first)
  {
    Node tmp(first->symbol, first->freq, getCode(ptr(&rootNode), first->symbol));
    dest.insert(tmp);
    first = getNext(first);
  }

  using outIt = std::ostream_iterator< Node >;
  std::copy(dest.cbegin(), dest.cend(), outIt(std::cout, "\n"));

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
    auto dPHKFirst = std::bind(&doesNodeHaveKey, std::placeholders::_1, firstIt->symbol);
    newNode.left = static_cast< ptr >(*std::find_if(tmpVector.begin(), tmpVector.end(), dPHKFirst));
    tmpVector.push_back




      codeTree.erase(firstIt);
    codeTree.erase(secondIt);
    codeTree.insert();
  }

  setType newAlph(compareNodes);
  alph.swap(fillSetWithCodes(newAlph, codeTree));

  return alph;
}


