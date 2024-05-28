#include <iostream>
#include "commands.hpp"
#include "entities.hpp"

int main()
{
  using namespace ibragimov;
  // std::string text = "Aah, you were at my side all along. My true mentor... My guiding moonlight...";
  DecodedText text("abracadabra");
  Encodings encodingTable1(createEncodings(text));
  EncodedText encodedText(encode(text, encodingTable1));
  DecodedText decodedText(decode(encodedText, encodingTable1));
  std::cout << encodedText.text << ' ' << encodedText.size << '\n';
  std::cout << decodedText.text << ' ' << decodedText.size << '\n';

  Encodings encodingTable2(createEncodings(DecodedText("abcdr")));
  EncodedText encodedText2(encode(text, encodingTable2));
  std::cout << encodedText2.text << ' ' << encodedText2.size << '\n';

  std::vector< Encodings > tables = {encodingTable1, encodingTable2};
  Encodings efficient(findEfficient(tables, text));
  Encodings unefficient(findUnefficient(tables, text));
  for (const std::pair< const char, std::string >& pair : efficient.encodingTable)
  {
    std::cout << pair.first << ' ' << pair.second << '\n';
  }
  for (const std::pair< const char, std::string >& pair : unefficient.encodingTable)
  {
    std::cout << pair.first << ' ' << pair.second << '\n';
  }
  return 0;
}
