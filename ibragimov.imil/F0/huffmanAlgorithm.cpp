#include "huffmanAlgorithm.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <string>

std::unique_ptr< ibragimov::Node > extractMinimum(std::queue< std::unique_ptr< ibragimov::Node > >&,
    std::queue< std::unique_ptr< ibragimov::Node > >&);

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
  while (!initialWeights.empty())
  {
    std::unique_ptr< ibragimov::Node > left = extractMinimum(initialWeights, combinedWeights);
    std::unique_ptr< ibragimov::Node > right = extractMinimum(initialWeights, combinedWeights);

    std::string key{left->pair.first + right->pair.first};
    size_t value = left->pair.second + right->pair.second;
    combinedWeights.push(std::make_unique< Node >(key, value, left, right));
  }
  return std::move(combinedWeights.front());
}

// std::map< char, size_t > ibragimov::createEncodingTable(std::unique_ptr< ibragimov::Node > huffmanTree)
// {
//   std::map< char, size_t > encodingTable{};
//   std::queue< Node* > queue{};
//   Node* current = huffmanTree.get();
//   while (!queue.empty())
// }

std::unique_ptr< ibragimov::Node > extractMinimum(std::queue< std::unique_ptr< ibragimov::Node > >& lhs,
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
