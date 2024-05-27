#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <functional>
#include <set>
#include <vector>

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
  bool mainCondition = (lhs.freq <= rhs.freq && lhs.symbol != rhs.symbol);
  bool zeroCondition = (lhs.symbol == 0) && (rhs.symbol == 0);
  bool notSameZeros = zeroCondition && (lhs.left != rhs.left);
  bool zeroCondWithSort = (lhs.freq <= rhs.freq) && notSameZeros;
  return mainCondition || zeroCondWithSort;
}
bool petrov::doesNodeHaveKey(const Node& node, char key)
{
  return node.symbol == key;
}
bool petrov::isEqual(const Node& n1, const Node& n2)
{
  return n1.symbol == n2.symbol && n1.freq == n2.freq;
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

    std::cout << newNode.left->symbol << " <==> " << newNode.right->symbol << std::endl;

    codeTree.erase(firstIt);
    codeTree.erase(secondIt);
    codeTree.insert(newNode);
  }

  setType newAlph(compareNodes);
  auto root = codeTree.begin();
  alph.swap(fillSetWithCodes(newAlph, std::make_shared< Node >(*root)));

  return alph;
}


