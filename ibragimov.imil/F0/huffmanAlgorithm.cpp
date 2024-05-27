#include "huffmanAlgorithm.hpp"

#include <algorithm>
#include <bitset>
#include <cctype>
#include <functional>
#include <ios>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <string>

std::unique_ptr< ibragimov::Node > extractMinimum(std::queue< std::unique_ptr< ibragimov::Node > >&,
    std::queue< std::unique_ptr< ibragimov::Node > >&);

void increment(std::string&);
char flip(const char&);

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
  // for (const std::pair< const size_t, char >& pair : lengthTable)
  // {
  //   std::cout << pair.first << ' ' << pair.second << '\n';
  // }
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
    increment(code);
    std::fill_n(std::back_inserter(code), currentPair->first - std::prev(currentPair)->first, '0');
    encodingTable[currentPair->second] = code;
  }
  return encodingTable;
}

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

void increment(std::string& code)
{
  auto lastFalse = std::find(code.rbegin(), code.rend(), '0');
  auto flipUpTo = (lastFalse != code.rend()) ? next(lastFalse) : code.rend();
  std::transform(code.rbegin(), flipUpTo, code.rbegin(), flip);
}

char flip(const char& c)
{
  return (c == '0') ? '1' : '0';
}
