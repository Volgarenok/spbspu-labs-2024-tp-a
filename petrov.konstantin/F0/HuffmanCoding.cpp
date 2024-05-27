#include "HuffmanCoding.hpp"
#include <vector>
#include <algorithm>
#include "utils.hpp"

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
