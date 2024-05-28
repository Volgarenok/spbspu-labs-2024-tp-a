#include <iostream>
#include "commands.hpp"
#include "entities.hpp"

int main()
{
  using namespace ibragimov;
  // std::string text = "Aah, you were at my side all along. My true mentor... My guiding moonlight...";
  DecodedText text("abracadabra");
  Encodings encodingTable1(createEncodings(text));
  Encodings encodingTable2(createEncodings(DecodedText("abcdr")));
  EncodedText encodedText(encode(text, encodingTable1));
  DecodedText decodedText(decode(encodedText, encodingTable1));
  std::cout << encodedText.text << ' ' << encodedText.size << '\n';
  std::cout << decodedText.text << ' ' << decodedText.size << '\n';

  return 0;
}
