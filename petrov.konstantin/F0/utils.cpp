#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <functional>
#include <set>

#include <vector>

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
petrov::setType& petrov::fillSetWithCodes(setType& dest, Node::cRP root)
{
  if (root)
  {
    dest.insert(*root);
    fillSetWithCodes(dest, root->left);
    fillSetWithCodes(dest, root->right);
  }
  return dest;
}
void petrov::givingParents(Node::cRP root)
{
  if (!root)
  {
    return;
  }
  if (root->left)
  {
    root->left->parent = root;
  }
  if (root->right)
  {
    root->right->parent = root;
  }
  givingParents(root->left);
  givingParents(root->right);
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
    newNode.left = std::make_shared< Node >(*std::find_if(tmpVector.begin(), tmpVector.end(), dPHKFirst));
    auto dPHKSecond = std::bind(&doesNodeHaveKey, std::placeholders::_1, secondIt->symbol);
    newNode.right = std::make_shared< Node >(*std::find_if(tmpVector.begin(), tmpVector.end(), dPHKSecond));
    tmpVector.push_back(newNode);

    codeTree.erase(firstIt);
    codeTree.erase(secondIt);
    codeTree.insert(Node(0, newFreq, ""));


  }

  setType newAlph(compareNodes);
  auto rootInSet = codeTree.begin();
  auto dPHKey = std::bind(&doesNodeHaveKey, std::placeholders::_1, rootInSet->symbol);
  auto root = std::find_if(tmpVector.cbegin(), tmpVector.cend(), dPHKey);
  alph.swap(fillSetWithCodes(newAlph, *root));

  return alph;
}


