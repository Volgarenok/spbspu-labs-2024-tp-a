#include "commands.hpp"
#include "entities.hpp"

#include "huffmanAlgorithm.hpp"

ibragimov::Encodings ibragimov::createEncodings(const DecodedText& text)
{
  return Encodings(createEncodingTable(text.text));
}
ibragimov::EncodedText ibragimov::encode(const DecodedText& text, const Encodings& table)
{
  return EncodedText(encode(text.text, table.encodingTable));
}
ibragimov::DecodedText ibragimov::decode(const EncodedText& text, const Encodings& table)
{
  return DecodedText(decode(text.text, table.encodingTable));
}

// double findEfficiency(const ibragimov::DecodedText&, const ibragimov::EncodedText&);
//
// bool ibragimov::compareEfficiency(const Encodings& lhs, const Encodings& rhs, const DecodedText& text)
// {
//   EncodedText lhsEncoded(encode(text.text, lhs.encodingTable));
//   EncodedText rhsEncoded(encode(text.text, rhs.encodingTable));
//   return findEfficiency(text, lhsEncoded) < findEfficiency(text, rhsEncoded);
// }
//
// double findEfficiency(const ibragimov::DecodedText& decoded, const ibragimov::EncodedText& encoded)
// {
//   return ((decoded.size - encoded.size) / static_cast< double >(decoded.size)) * 100;
// }
