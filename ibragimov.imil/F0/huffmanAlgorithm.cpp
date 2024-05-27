#include "huffmanAlgorithm.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <string>

namespace detail
{
  std::unique_ptr< ibragimov::Node > extractMinimum(std::queue< std::unique_ptr< ibragimov::Node > >&,
      std::queue< std::unique_ptr< ibragimov::Node > >&);

  void increment(std::string&);
  char flip(const char&);

  void replaceSubstring(std::string&, const std::string&, const std::string&);
}

std::map< char, std::string > ibragimov::createEncodingTable(const std::string& text)
{
  std::multimap< size_t, char > table = createFrequencyTable(text);
  table = createCodesLengthTable(createHuffmanTree(table));
  return createEncodingTable(table);
}
std::string ibragimov::encode(const std::string& text, const std::map< char, std::string >& encodings)
{
  std::string encodedText = text;
  for (const std::pair< const char, std::string >& pair : encodings)
  {
    detail::replaceSubstring(encodedText, std::string{pair.first}, pair.second);
  }
  return encodedText;
}
std::string ibragimov::decode(const std::string& text, const std::map< char, std::string >& encodings)
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

std::multimap< size_t, char > ibragimov::createFrequencyTable(const std::string& text)
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
std::unique_ptr< ibragimov::Node > ibragimov::createHuffmanTree(const std::multimap< size_t, char >& frequencyTable)
{
  std::queue< std::unique_ptr< Node > > initialWeights{};
  for (const std::pair< const size_t, char > pair : frequencyTable)
  {
    initialWeights.push(std::make_unique< Node >(std::string{pair.second}, pair.first));
  }
  std::queue< std::unique_ptr< Node > > combinedWeights{};
  while (!initialWeights.empty() || combinedWeights.size() > 1)
  {
    std::unique_ptr< ibragimov::Node > left = detail::extractMinimum(initialWeights, combinedWeights);
    std::unique_ptr< ibragimov::Node > right = detail::extractMinimum(initialWeights, combinedWeights);

    std::string key{left->pair.first + right->pair.first};
    size_t value = left->pair.second + right->pair.second;
    combinedWeights.push(std::make_unique< Node >(key, value, left, right));
  }
  return std::move(combinedWeights.front());
}
std::multimap< size_t, char > ibragimov::createCodesLengthTable(const std::unique_ptr< ibragimov::Node >& huffmanTree)
{
  std::multimap< size_t, char > lengthsTable{};
  {
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
          std::pair< size_t, char > pair{height, current->pair.first[0]};
          lengthsTable.insert(pair);
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
  }
  return lengthsTable;
}
std::map< char, std::string > ibragimov::createEncodingTable(const std::multimap< size_t, char >& lengthsTable)
{
  std::map< char, std::string > encodingTable{};
  auto currentPair = lengthsTable.cbegin();
  std::string code(currentPair->first, '0');
  encodingTable[currentPair->second] = code;
  for (currentPair = next(currentPair); currentPair != lengthsTable.cend(); ++currentPair)
  {
    detail::increment(code);
    std::fill_n(std::back_inserter(code), currentPair->first - std::prev(currentPair)->first, '0');
    encodingTable[currentPair->second] = code;
  }
  return encodingTable;
}

std::unique_ptr< ibragimov::Node > detail::extractMinimum(std::queue< std::unique_ptr< ibragimov::Node > >& lhs,
    std::queue< std::unique_ptr< ibragimov::Node > >& rhs)
{
  std::unique_ptr< ibragimov::Node > node{};
  if (lhs.empty())
  {
    node = std::move(rhs.front());
    rhs.pop();
  }
  else if (rhs.empty())
  {
    node = std::move(lhs.front());
    lhs.pop();
  }
  else if (lhs.front()->pair.second <= rhs.front()->pair.second)
  {
    node = std::move(lhs.front());
    lhs.pop();
  }
  else
  {
    node = std::move(rhs.front());
    rhs.pop();
  }
  return node;
}

void detail::increment(std::string& code)
{
  auto lastFalse = std::find(code.rbegin(), code.rend(), '0');
  auto flipUpTo = (lastFalse != code.rend()) ? next(lastFalse) : code.rend();
  std::transform(code.rbegin(), flipUpTo, code.rbegin(), detail::flip);
}

char detail::flip(const char& c)
{
  return (c == '0') ? '1' : '0';
}

void detail::replaceSubstring(std::string& str, const std::string& toReplace, const std::string& replaceWith)
{
  if (toReplace.empty() || str.empty() || replaceWith.empty())
  {
    throw std::invalid_argument("");
  }
  size_t pos = str.find(toReplace, 0);
  while (pos != std::string::npos)
  {
    str.replace(pos, toReplace.size(), replaceWith);
    pos = str.find(toReplace, pos);
  }
}
