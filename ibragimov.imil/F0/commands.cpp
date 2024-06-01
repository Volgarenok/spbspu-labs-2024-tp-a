#include "commands.hpp"

#include <algorithm>
#include <functional>
#include <memory>
#include "entities.hpp"
#include "huffmanAlgorithm.hpp"

namespace ibragimov
{
  namespace detail
  {
    size_t calculateEfficiency(const ibragimov::DecodedText&, const ibragimov::EncodedText&);
    bool compareEfficiency(const Encodings&, const Encodings&, const DecodedText&);
    Encodings createEncodings(const DecodedText&);
    EncodedText encode(const DecodedText&, const Encodings&);
    DecodedText decode(const EncodedText&, const Encodings&);
  }
}

void ibragimov::huffman(const std::vector< std::shared_ptr< DecodedText > >& texts, const size_t pos, std::shared_ptr< Entity >& current)
{
  std::shared_ptr< Encodings > encoding = std::make_shared< Encodings >(detail::createEncodings(*texts.at(pos)));
  current = std::move(encoding);
}
void ibragimov::encode(const std::vector< std::shared_ptr< DecodedText > >& texts, const size_t pos1,
    const std::vector< std::shared_ptr< Encodings > >& encodings, const size_t pos2, std::shared_ptr< Entity >& current)
{
  std::shared_ptr< EncodedText > encoded = std::make_shared< EncodedText >(detail::encode(*texts.at(pos1), *encodings.at(pos2)));
  current = std::move(encoded);
}
void ibragimov::decode(const std::vector< std::shared_ptr< EncodedText > >& texts, const size_t pos1,
    const std::vector< std::shared_ptr< Encodings > >& encodings, const size_t pos2, std::shared_ptr< Entity >& current)
{
  std::shared_ptr< DecodedText > decoded = std::make_shared< DecodedText >(detail::decode(*texts.at(pos1), *encodings.at(pos2)));
  current = std::move(decoded);
}

ibragimov::Encodings ibragimov::detail::createEncodings(const DecodedText& text)
{
  return Encodings(createEncodingTable(text.text));
}
ibragimov::EncodedText ibragimov::detail::encode(const DecodedText& text, const Encodings& table)
{
  return EncodedText(encode(text.text, table.encodingTable));
}
ibragimov::DecodedText ibragimov::detail::decode(const EncodedText& text, const Encodings& table)
{
  return DecodedText(decode(text.text, table.encodingTable));
}
ibragimov::Encodings ibragimov::findEfficient(const std::vector< Encodings >& tables, const DecodedText& text)
{
  using namespace std::placeholders;
  auto comparator = std::bind(ibragimov::detail::compareEfficiency, _1, _2, text);
  return *std::max_element(tables.cbegin(), tables.cend(), comparator);
}
ibragimov::Encodings ibragimov::findUnefficient(const std::vector< Encodings >& tables, const DecodedText& text)
{
  using namespace std::placeholders;
  auto comparator = std::bind(ibragimov::detail::compareEfficiency, _1, _2, text);
  return *std::min_element(tables.cbegin(), tables.cend(), comparator);
}
std::vector< ibragimov::Encodings > ibragimov::compareEncodings(const std::vector< Encodings >& tables, const DecodedText& text)
{
  std::vector< ibragimov::Encodings > copiedTables = tables;
  using namespace std::placeholders;
  auto comparator = std::bind(ibragimov::detail::compareEfficiency, _1, _2, text);
  std::sort(copiedTables.begin(), copiedTables.end(), comparator);
  return copiedTables;
}

size_t ibragimov::detail::calculateEfficiency(const ibragimov::DecodedText& decoded, const ibragimov::EncodedText& encoded)
{
  return (decoded.bits - encoded.bits);
}
bool ibragimov::detail::compareEfficiency(const Encodings& lhs, const Encodings& rhs, const DecodedText& text)
{
  EncodedText lhsEncoded(encode(text.text, lhs.encodingTable));
  EncodedText rhsEncoded(encode(text.text, rhs.encodingTable));
  return calculateEfficiency(text, lhsEncoded) < calculateEfficiency(text, rhsEncoded);
}
