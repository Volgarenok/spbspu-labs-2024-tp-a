#include "huffmanAlgorithm.hpp"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iterator>
#include <list>
#include <memory>
#include <queue>
#include <string>
#include <utility>
#include "huffmanNode.hpp"

namespace ibragimov
{
  namespace detail
  {
    std::multimap< size_t, char > createFrequencyTable(const std::string&);
    std::unique_ptr< Node > createHuffmanTree(const std::multimap< size_t, char >&);
    std::multimap< size_t, char > createCodesLengthTable(const std::unique_ptr< Node >&);
    std::map< char, std::string > createEncodingTable(const std::multimap< size_t, char >&);

    std::unique_ptr< Node > extractMinimum(std::list< std::unique_ptr< Node > >&);
    bool isMinWeight(const std::unique_ptr< Node >&, const std::unique_ptr< Node >&);

    std::pair< char, std::string > createNewEncoding(const std::pair< size_t, char >& current,
        const std::pair< size_t, char >& prev, std::string& code);
    void increment(std::string&);
    char flip(const char&);

    void replaceSubstring(std::string&, const std::string&, const std::string&);
  }
}

std::map< char, std::string > ibragimov::detail::createEncodingTable(const std::string& text)
{
  using namespace detail;
  std::multimap< size_t, char > table{createCodesLengthTable(createHuffmanTree(createFrequencyTable(text)))};
  return detail::createEncodingTable(table);
}
std::string ibragimov::detail::encode(const std::string& text, const std::map< char, std::string >& encodings)
{
  std::string encodedText = text;
  for (const std::pair< const char, std::string >& pair : encodings)
  {
    detail::replaceSubstring(encodedText, std::string{pair.first}, pair.second);
  }
  return encodedText;
}
std::string ibragimov::detail::decode(const std::string& text, const std::map< char, std::string >& encodings)
{
  std::map< std::string, char > copiedEncodings{};
  for (const std::pair< const char, std::string >& pair : encodings)
  {
    copiedEncodings[pair.second] = pair.first;
  }
  std::string decodedText{};
  std::string code{};
  for (const char bit : text)
  {
    code.push_back(bit);
    if (copiedEncodings.find(code) != copiedEncodings.end())
    {
      decodedText.push_back(copiedEncodings[code]);
      code.clear();
    }
  }
  return decodedText;
}

std::multimap< size_t, char > ibragimov::detail::createFrequencyTable(const std::string& text)
{
  std::string copiedText{text};
  std::sort(copiedText.begin(), copiedText.end());
  std::string alphabet{};
  std::unique_copy(copiedText.cbegin(), copiedText.cend(), std::back_inserter(alphabet));
  std::multimap< size_t, char > frequencyTable{};
  for (char c : alphabet)
  {
    size_t value = std::count(copiedText.cbegin(), copiedText.cend(), c);
    frequencyTable.insert(std::pair< size_t, char >{value, c});
  }
  return frequencyTable;
}
std::unique_ptr< ibragimov::detail::Node > ibragimov::detail::createHuffmanTree(const std::multimap< size_t, char >& frequencyTable)
{
  std::list< std::unique_ptr< Node > > weights{};
  for (const std::pair< const size_t, char > pair : frequencyTable)
  {
    weights.push_back(std::make_unique< Node >(pair));
  }
  while (weights.size() > 1)
  {
    std::unique_ptr< Node > left = detail::extractMinimum(weights);
    std::unique_ptr< Node > right = detail::extractMinimum(weights);

    weights.push_back(std::make_unique< Node >(left->pair.first + right->pair.first, left, right));
  }
  return std::move(weights.back());
}
std::multimap< size_t, char > ibragimov::detail::createCodesLengthTable(const std::unique_ptr< Node >& huffmanTree)
{
  std::multimap< size_t, char > lengthsTable{};
  std::queue< Node* > queue{};
  queue.push(huffmanTree.get());
  size_t height = 0;
  while (!queue.empty())
  {
    size_t numberOfNodes = queue.size();
    while (numberOfNodes--)
    {
      Node* current = queue.front();
      queue.pop();
      if (!current->left && !current->right)
      {
        lengthsTable.insert(std::make_pair(height, current->pair.second));
      }
      if (current->left)
      {
        queue.push(current->left.get());
      }
      if (current->right)
      {
        queue.push(current->right.get());
      }
    }
    ++height;
  }
  return lengthsTable;
}
std::map< char, std::string > ibragimov::detail::createEncodingTable(const std::multimap< size_t, char >& lengths)
{
  std::map< char, std::string > encodings{};
  std::string code(lengths.cbegin()->first, '0');
  using namespace std::placeholders;
  auto functor = std::bind(createNewEncoding, _1, _2, code);
  encodings[lengths.cbegin()->second] = code;
  std::transform(next(lengths.cbegin()), lengths.cend(), lengths.cbegin(),
      std::inserter(encodings, std::next(encodings.begin())), functor);
  return encodings;
}

std::unique_ptr< ibragimov::detail::Node > ibragimov::detail::extractMinimum(std::list< std::unique_ptr< Node > >& list)
{
  auto minIter = std::min_element(list.begin(), list.end(), isMinWeight);
  std::unique_ptr< Node > minNode;
  if (minIter != list.end())
  {
    minNode = std::move(*minIter);
    list.erase(std::remove(list.begin(), list.end(), *minIter), list.end());
  }
  return minNode;
}
bool ibragimov::detail::isMinWeight(const std::unique_ptr< Node >& lhs, const std::unique_ptr< Node >& rhs)
{
  return lhs->pair.first <= rhs->pair.first;
}

std::pair< char, std::string > ibragimov::detail::createNewEncoding(const std::pair< size_t, char >& current,
    const std::pair< size_t, char >& prev, std::string& code)
{
  detail::increment(code);
  std::fill_n(std::back_inserter(code), current.first - prev.first, '0');
  return std::make_pair(current.second, code);
}
void ibragimov::detail::increment(std::string& code)
{
  auto lastFalse = std::find(code.rbegin(), code.rend(), '0');
  auto flipUpTo = (lastFalse != code.rend()) ? next(lastFalse) : code.rend();
  std::transform(code.rbegin(), flipUpTo, code.rbegin(), flip);
}
char ibragimov::detail::flip(const char& c)
{
  return (c == '0') ? '1' : '0';
}

void ibragimov::detail::replaceSubstring(std::string& str, const std::string& toReplace, const std::string& replaceWith)
{
  if (toReplace.empty() || str.empty() || replaceWith.empty())
  {
    throw std::invalid_argument("");
  }
  for (size_t pos = str.find(toReplace); pos != std::string::npos; pos = str.find(toReplace, pos))
  {
    str.replace(pos, toReplace.size(), replaceWith);
  }
}
