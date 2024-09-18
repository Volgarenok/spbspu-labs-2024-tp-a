#include "dictionary.hpp"
#include <algorithm>
#include <iterator>
#include <functional>
#include <delimeter.hpp>

piyavkin::Node::Node():
  pair({"", 0})
{}

piyavkin::Node::Node(const std::pair< std::string, size_t >& pr):
  pair(pr)
{}

std::istream& piyavkin::operator>>(std::istream& in, Node& node)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::string str = "";
  size_t val = 0;
  using dc = DelimeterChar;
  in >> str >> dc{'-'} >> val;
  if (in)
  {
    node.pair = std::make_pair< std::string, size_t >(std::move(str), std::move(val));
  }
  return in;
}

std::ostream& piyavkin::operator<<(std::ostream& out, const Node& node)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << node.pair.first << " - " << node.pair.second;
  return out;
}

std::pair< std::string, size_t > piyavkin::getNode(const Node& node)
{
  return node.pair;
}

std::istream& piyavkin::operator>>(std::istream& in, Dictionary& dic)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using input_it_t = std::istream_iterator< Node >;
  std::map< std::string, size_t > temp;
  std::transform(input_it_t{in}, input_it_t{}, std::inserter(temp, temp.end()), getNode);
  if (in.eof())
  {
    dic.dic = temp;
  }
  return in;
}

piyavkin::Node piyavkin::getVal(const std::pair< std::string, size_t >& node)
{
  return Node(node);
}

std::ostream& piyavkin::operator<<(std::ostream& out, const Dictionary& dic)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  std::transform(dic.dic.cbegin(), dic.dic.cend(), std::ostream_iterator< Node >{out, "\n"}, getVal);
  return out;
}
