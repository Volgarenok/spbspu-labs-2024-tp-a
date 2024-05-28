#include "dictionary.hpp"
#include <algorithm>
#include <iterator>
#include <delimeter.hpp>

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