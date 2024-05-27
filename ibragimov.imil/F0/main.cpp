#include <iostream>
#include <map>
#include "huffmanAlgorithm.hpp"

int main()
{
  // std::string text = "Aah, you were at my side all along. My true mentor... My guiding moonlight...";
  std::string text = "abracadabra";
  std::map< char, std::string > encodingTable = ibragimov::createEncodingTable(text);
  std::string encodedText = ibragimov::encode(text, encodingTable);
  std::string decodedText = ibragimov::decode(encodedText, encodingTable);
  std::cout << encodedText << ' ' << encodedText.size() << '\n';
  std::cout << decodedText << ' ' << decodedText.size() << '\n';
  std::map< char, std::string > encodingTable2 = ibragimov::createEncodingTable("abrcd");
  std::cout << ibragimov::findEfficency(text, encodingTable) << '\n';
  std::cout << ibragimov::encode(text, encodingTable2) << '\n';
  std::cout << ibragimov::findEfficency(text, encodingTable2) << '\n';
  return 0;
}
