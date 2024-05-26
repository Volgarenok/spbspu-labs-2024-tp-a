#include "utils.hpp"
#include <memory>
#include <algorithm>
#include <functional>
#include <set>

petrov::Node::Node(char sym = 0, size_t frequency = 1):
  symbol(sym),
  freq(frequency)
{}
petrov::Node::Node(const shared_ptr& lhs, const shared_ptr& rhs):
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
