#include "commands.hpp"

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include "entities.hpp"
#include "huffmanAlgorithm.hpp"

namespace ibragimov
{
  namespace detail
  {
    template < class T >
    T getData(const std::shared_ptr< T >&);
    template < class T >
    std::shared_ptr< T > findData(const std::vector< std::shared_ptr< T > >&, const size_t);
    Encodings createEncodings(const DecodedText&);
    EncodedText encode(const DecodedText&, const Encodings&);
    DecodedText decode(const EncodedText&, const Encodings&);
    bool compareEfficiency(const std::shared_ptr< Encodings >&, const std::shared_ptr< Encodings >&,
        const DecodedText&);
    size_t calculateEfficiency(const DecodedText&, const EncodedText&);
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
  }
  catch (const std::exception&)
  {
    throw std::invalid_argument("");
  }
}
void ibragimov::deleteFromMemory(const std::map< std::string, std::function< void(std::istream&) > >& subCommands, std::istream& in)
{
  std::string input{};
  in >> input;
  std::function< void(std::istream&) > command;
  try
  {
    command = subCommands.at(input);
    command(in);
  }
  catch (const std::exception&)
  {
    throw std::invalid_argument("");
  }
}
void ibragimov::loadFromMemory(const std::map< std::string, std::function< void(std::istream&) > >& subCommands, std::istream& in)
{
  std::string input{};
  in >> input;
  std::function< void(std::istream&) > command;
  try
  {
    command = subCommands.at(input);
    command(in);
  }
  catch (const std::exception&)
  {
    throw std::invalid_argument("");
  }
}
void ibragimov::printInfo(const std::map< std::string, std::function< void() > >& subCommands, std::istream& in)
{
  std::string input{};
  in >> input;
  std::function< void() > command;
  try
  {
    command = subCommands.at(input);
    command();
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
void ibragimov::compare(const std::vector< std::shared_ptr< Encodings > >& encodings, std::istream& in)
{
  using namespace std::placeholders;
  auto functor = std::bind(detail::findData< Encodings >, encodings, _1);
  std::vector< std::shared_ptr< Encodings > > correct{};
  using is_iter = std::istream_iterator< size_t >;
  std::transform(is_iter{in}, is_iter{}, std::back_inserter(correct), functor);
  DecodedText test{};
  in >> test;
  auto comparator = std::bind(detail::compareEfficiency, _1, _2, test);
  std::sort(correct.begin(), correct.end(), comparator);
  printEncodings(correct);
}
void ibragimov::find(const std::map< std::string, std::function< void(std::istream&) > >& subCommands,
    std::istream& in)
{
  std::string input{};
  in >> input;
  std::function< void(std::istream&) > command;
  try
  {
    command = subCommands.at(input);
    command(in);
  }
  catch (const std::exception&)
  {
    throw std::invalid_argument("");
  }
}

size_t ibragimov::inputPos(std::istream& in)
{
  size_t pos = 0;
  in >> pos;
  if (!in)
  {
    throw std::invalid_argument("");
  }
  return pos;
}
void ibragimov::printCurrent(const std::shared_ptr< Entity >& current)
{
  if (!current)
  {
    throw std::invalid_argument("");
  }
  else
  {
    current->outputInfo();
  }
}
void ibragimov::printAll(const std::vector< std::shared_ptr< DecodedText > >& decoded,
    const std::vector< std::shared_ptr< EncodedText > >& encoded,
    const std::vector< std::shared_ptr< Encodings > >& encodings)
{
  if (!decoded.empty() && !encoded.empty() && encodings.empty())
  {
    throw std::invalid_argument("");
  }
  if (!decoded.empty())
  {
    std::cout << "DECODED:\n";
    printDecoded(decoded);
  }
  if (!encoded.empty())
  {
    std::cout << "ENCODED:\n";
    printEncoded(encoded);
  }
  if (encodings.empty())
  {
    std::cout << "ENCODINGS:\n";
    printEncodings(encodings);
  }
}
void ibragimov::printDecoded(const std::vector< std::shared_ptr< DecodedText > >& decoded)
{
  if (decoded.empty())
  {
    throw std::invalid_argument("");
  }
  using os_iter = std::ostream_iterator< DecodedText >;
  std::transform(decoded.cbegin(), decoded.cend(), os_iter{std::cout, "\n"}, detail::getData< DecodedText >);
}
void ibragimov::printEncoded(const std::vector< std::shared_ptr< EncodedText > >& encoded)
{
  if (encoded.empty())
  {
    throw std::invalid_argument("");
  }
  using os_iter = std::ostream_iterator< EncodedText >;
  std::transform(encoded.cbegin(), encoded.cend(), os_iter{std::cout, "\n"}, detail::getData< EncodedText >);
}
void ibragimov::printEncodings(const std::vector< std::shared_ptr< Encodings > >& encodings)
{
  if (encodings.empty())
  {
    throw std::invalid_argument("");
  }
  using os_iter = std::ostream_iterator< Encodings >;
  std::transform(encodings.cbegin(), encodings.cend(), os_iter{std::cout, "\n"}, detail::getData< Encodings >);
}
void ibragimov::findEfficient(const std::vector< std::shared_ptr< DecodedText > >& decoded, const size_t pos,
    const std::vector< std::shared_ptr< Encodings > >& encodings)
{
  using namespace std::placeholders;
  auto comparator = std::bind(ibragimov::detail::compareEfficiency, _1, _2, *decoded.at(pos));
  std::cout << detail::getData(*std::max_element(encodings.cbegin(), encodings.cend(), comparator)) << '\n';
}
void ibragimov::findUnefficient(const std::vector< std::shared_ptr< DecodedText > >& decoded, const size_t pos,
    const std::vector< std::shared_ptr< Encodings > >& encodings)
{
  using namespace std::placeholders;
  auto comparator = std::bind(ibragimov::detail::compareEfficiency, _1, _2, *decoded.at(pos));
  std::cout << detail::getData(*std::min_element(encodings.cbegin(), encodings.cend(), comparator)) << '\n';
}

template < class T >
T ibragimov::detail::getData(const std::shared_ptr< T >& rhs)
{
  return *rhs;
}
template < class T >
std::shared_ptr< T > ibragimov::detail::findData(const std::vector< std::shared_ptr< T > >& vector, const size_t pos)
{
  return vector.at(pos);
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
bool ibragimov::detail::compareEfficiency(const std::shared_ptr< Encodings >& lhs, const std::shared_ptr< Encodings >& rhs,
    const DecodedText& decoded)
{
  EncodedText lhsEncoded(encode(decoded.text, lhs->encodingTable));
  EncodedText rhsEncoded(encode(decoded.text, rhs->encodingTable));
  return calculateEfficiency(decoded, lhsEncoded) < calculateEfficiency(decoded, rhsEncoded);
}
size_t ibragimov::detail::calculateEfficiency(const DecodedText& decoded, const EncodedText& encoded)
{
  return (decoded.bits - encoded.bits);
}
