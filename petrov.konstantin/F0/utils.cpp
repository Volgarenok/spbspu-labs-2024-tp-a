#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <functional>
#include <set>

petrov::Node::Node(char nSym = 0, size_t nFreq = 1, str nCode = "", cRP lhs = nullptr, cRP rhs = nullptr):
  symbol(nSym),
  freq(nFreq),
  code(nCode),
  left(lhs),
  right(rhs)
{}
std::ostream& petrov::operator<<(std::ostream& out, const Node& node)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << node.symbol << " : " << node.freq;
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

void petrov::fillCodes(setType& alph)
{
  setType tmpSet(alph);
  Node tmpNode;
  while (tmpSet.size() > 1)
  {
    auto tmpIt = tmpSet.begin();
    Node first = *tmpIt;
    Node second = *(++tmpIt);
    size_t newFreq = first.freq + second.freq;
    std::string newCode = "";
    std::shared_ptr< Node > shPtrFir(&first);
    std::shared_ptr< Node > shPtrSec(&second);
    Node newNode(0, newFreq, newCode, shPtrFir, shPtrSec);

    tmpSet.erase(first);
    tmpSet.erase(second);
    tmpSet.insert(newNode);
  }

}


