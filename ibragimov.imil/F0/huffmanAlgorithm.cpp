#include "huffmanAlgorithm.hpp"

#include <algorithm>
#include <iterator>
#include <queue>
#include <string>

std::map< char, size_t > ibragimov::createFrequencyTable(const std::string& text)
{
  std::string copiedText{text};
  std::sort(copiedText.begin(), copiedText.end());
  std::string alphabet{};
  std::unique_copy(copiedText.cbegin(), copiedText.cend(), std::back_inserter(alphabet));
  std::map< char, size_t > frequencyTable{};
  for (char key : alphabet)
  {
    frequencyTable[key] = std::count(copiedText.cbegin(), copiedText.cend(), key);
  }
  return frequencyTable;
}

// std::unique_ptr< ibragimov::Node > ibragimov::createHuffmanTree(const std::map< char, size_t >& frequencyTable)
// {
//   std::queue< Node > initialWeights{};
//   for (const std::pair< const char, size_t > pair : frequencyTable)
//   {
//     initialWeights.push(Node(pair))
//   }
// }
