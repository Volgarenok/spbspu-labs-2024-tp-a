#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <functional>
#include <set>

petrov::Node::Node(char sym = 0):
  symbol(sym)
{}
petrov::Node::Node(const shared_ptr& lhs, const shared_ptr& rhs):
  left(lhs),
  right(rhs)
{}
std::ostream& petrov::operator<<(std::ostream& out, const Node& node)
{
  return out << node.symbol;
}
bool petrov::compareNodes(const Node& lhs, const Node& rhs)
{
  return lhs.symbol < rhs.symbol;
}
bool petrov::doesNodeHaveKey(const Node& node, char key)
{
  return node.symbol == key;
}
bool petrov::comparePairs(const pairType& lhs, const pairType& rhs)
{
  return lhs.second <= rhs.second && lhs.first.symbol != rhs.first.symbol;
}
bool petrov::doesPairHaveKey(const pairType& pair, char key)
{
  return doesNodeHaveKey(pair.first, key);
}
std::ostream& petrov::operator<<(std::ostream& out, pairType pair)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  return out << pair.first.symbol << " : " << pair.second;
}

void petrov::addToSet(setType& alph, char symbol)
{
  auto dPHKey = std::bind(&doesPairHaveKey, std::placeholders::_1, symbol);
  auto element = std::find_if(alph.begin(), alph.end(), dPHKey);
  if (element != alph.end())
  {
    pairType tmp = (*element);
    alph.erase(element);
    tmp.second += 1;
    alph.insert(tmp);
  }
  else
  {
    alph.insert(pairType(Node(symbol), 1));
  }
}
