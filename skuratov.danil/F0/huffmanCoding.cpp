#include "huffmanCoding.hpp"

void skuratov::storeCodes(HuffmanTreeNode* root, const std::string& str, std::map< char, std::string >& huffmanCodes)
{
  if (root == nullptr)
  {
    return;
  }
  if (root->data != '$')
  {
    huffmanCodes[root->data] = str;
  }
  storeCodes(root->left, str + "0", huffmanCodes);
  storeCodes(root->right, str + "1", huffmanCodes);
}

void skuratov::createHuffmanCodes(const std::string& text, std::map< char, std::string >& huffmanCodes)
{
  std::map< char, int > freq;
  for (char c : text)
  {
    freq[c]++;
  }

  std::priority_queue< HuffmanTreeNode*, std::vector< HuffmanTreeNode* >, Compare > minHeap;

  for (const auto& pair : freq)
  {
    minHeap.push(new HuffmanTreeNode(pair.first, pair.second));
  }

  while (minHeap.size() > 1)
  {
    HuffmanTreeNode* left = minHeap.top();
    minHeap.pop();
    HuffmanTreeNode* right = minHeap.top();
    minHeap.pop();

    HuffmanTreeNode* top = new HuffmanTreeNode('$', left->freq + right->freq);
    top->left = left;
    top->right = right;
    minHeap.push(top);
  }

  storeCodes(minHeap.top(), "", huffmanCodes);
}

bool skuratov::compressText(const std::string& text, const std::map< char, std::string >& huffmanCodes, std::string& encodedText)
{
  for (char c : text)
  {
    if (huffmanCodes.find(c) == huffmanCodes.end())
    {
      return false;
    }
    encodedText += huffmanCodes.at(c);
  }
  return true;
}

bool skuratov::decompressText(const std::string& encodedText, const std::map< char, std::string >& huffmanCodes, std::string& decodedText)
{
  std::map< std::string, char > reverseCodes;
  for (const auto& pair : huffmanCodes)
  {
    reverseCodes[pair.second] = pair.first;
  }

  std::string currentCode = "";
  for (char bit : encodedText)
  {
    currentCode += bit;
    auto it = reverseCodes.find(currentCode);
    if (it != reverseCodes.end())
    {
      decodedText += it->second;
      currentCode.clear();
    }
  }
  return currentCode.empty();
}

double skuratov::calculateEfficiency(const std::string& text, const std::map< char, std::string >& huffmanCodes)
{
  double originalSize = text.size() * 8;
  double compressedSize = 0;

  for (char c : text)
  {
    compressedSize += huffmanCodes.at(c).size();
  }
  return (originalSize - compressedSize) / originalSize * 100;
}

bool skuratov::compareByLength(const std::string& a, const std::string& b)
{
  return a.length() < b.length();
}
