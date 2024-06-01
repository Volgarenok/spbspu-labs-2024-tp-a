#include "commands.hpp"

#include <exception>
#include <iostream>
#include "entities.hpp"
#include "huffmanAlgorithm.hpp"

namespace ibragimov
{
  namespace detail
  {
    Encodings createEncodings(const DecodedText&);
    EncodedText encode(const DecodedText&, const Encodings&);
    DecodedText decode(const EncodedText&, const Encodings&);
  }
}
void ibragimov::input(const std::map< std::string, std::function< void(std::istream&) > >& subCommands, std::istream& in)
{
  std::string input{};
  in >> input;
  std::function< void(std::istream&) > command;
  try
  {
    command = subCommands.at(input);
    command(in);
    std::cout << "Success\n";
  }
  catch (const std::exception&)
  {
    throw std::invalid_argument("");
  }
}
void ibragimov::saveIntoMemory(const std::map< std::string, std::function< void() > >& subCommands, std::istream& in)
{
  std::string input{};
  in >> input;
  std::function< void() > command;
  try
  {
    command = subCommands.at(input);
    command();
    std::cout << "Success\n";
  }
  catch (const std::exception&)
  {
    throw std::invalid_argument("");
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
