#include <iostream>
#include <map>
#include "huffmanAlgorithm.hpp"

int main()
{
  std::string text = "Aah, you were at my side all along. My true mentor... My guiding moonlight...";
  std::map< char, std::string > encodingTable = ibragimov::createEncodingTable(text);
  std::string encodedText = ibragimov::encode(text, encodingTable);
  std::string decodedText = ibragimov::decode(encodedText, encodingTable);
  std::cout << encodedText << ' ' << encodedText.size() << '\n';
  std::cout << decodedText << ' ' << decodedText.size() << '\n';
  return 0;
}
