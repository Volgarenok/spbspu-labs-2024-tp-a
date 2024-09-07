#include "entities.hpp"

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include "../common/inputFormatters.hpp"
#include "../common/label.hpp"
#include "../common/strategies.hpp"
#include "../common/streamGuard.hpp"

namespace ibragimov
{
  namespace detail
  {
    struct EncodingPair
    {
      std::pair< char, std::string > pair;
    };
    std::istream& operator>>(std::istream&, EncodingPair&);
    std::ostream& operator<<(std::ostream&, const EncodingPair&);
    EncodingPair makeEncodingPair(const std::pair< char, std::string >&);
    std::pair< char, std::string > getPair(const EncodingPair&);
  }
}

ibragimov::Encodings::Encodings(const std::map< char, std::string >& rhs):
  encodingTable(rhs)
{}
std::istream& ibragimov::operator>>(std::istream& in, Encodings& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  ibragimov::StreamGuard sGuard(in);
  using namespace ibragimov::formatters;
  using namespace ibragimov::detail;
  using Delimiter = LabelI< CaseSensitive >;
  in >> std::noskipws;
  in >> Delimiter{"("};
  std::vector< EncodingPair > temp{};
  using is_iter = std::istream_iterator< EncodingPair >;
  std::copy(is_iter{in}, is_iter{}, std::back_inserter(temp));
  in >> Delimiter{")"};
  std::transform(temp.cbegin(), temp.cend(), std::inserter(rhs.encodingTable, rhs.encodingTable.begin()), getPair);
  return in;
}
std::ostream& ibragimov::operator<<(std::ostream& out, const Encodings& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using namespace ibragimov::detail;
  out << '(';
  using os_iter = std::ostream_iterator< EncodingPair >;
  std::transform(rhs.encodingTable.cbegin(), rhs.encodingTable.cend(), os_iter{out}, makeEncodingPair);
  out << ')';
  return out;
}
void ibragimov::Encodings::outputInfo()
{
  std::cout << "TYPE: ENCODINGS TABLE\n";
  std::cout << "DATA: " << *this << '\n';
}

ibragimov::DecodedText::DecodedText(const std::string& rhs):
  text(rhs),
  size(rhs.size()),
  bits(size * 8)
{}
std::istream& ibragimov::operator>>(std::istream& in, DecodedText& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using namespace ibragimov::formatters;
  std::string temp{};
  in >> StringI{temp};
  if (in)
  {
    rhs = DecodedText(temp);
  }
  return in;
}
std::ostream& ibragimov::operator<<(std::ostream& out, const DecodedText& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << std::quoted(rhs.text);
  return out;
}
void ibragimov::DecodedText::outputInfo()
{
  std::cout << "TYPE: DECODED TEXT\n";
  std::cout << "DATA: " << *this << '\n';
}

ibragimov::EncodedText::EncodedText(const std::string& rhs):
  text(rhs),
  size(rhs.size()),
  bits(size)
{}
std::istream& ibragimov::operator>>(std::istream& in, EncodedText& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using namespace ibragimov::formatters;
  std::string temp{};
  in >> StringI{temp};
  if (in)
  {
    rhs = EncodedText(temp);
  }
  return in;
}
std::ostream& ibragimov::operator<<(std::ostream& out, const EncodedText& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << std::quoted(rhs.text);
  return out;
}
void ibragimov::EncodedText::outputInfo()
{
  std::cout << "TYPE: ENCODED TEXT\n";
  std::cout << "DATA: " << *this << '\n';
}

std::istream& ibragimov::detail::operator>>(std::istream& in, EncodingPair& rhs)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  ibragimov::StreamGuard sGuard(in);
  using namespace ibragimov::formatters;
  using Delimiter = LabelI< CaseSensitive >;
  std::pair< char, std::string > temp;
  in >> std::noskipws;
  in >> Delimiter{"("} >> temp.first >> Delimiter{":"} >> StringI{temp.second} >> Delimiter{")"};
  if (in)
  {
    rhs.pair = temp;
  }
  return in;
}
std::ostream& ibragimov::detail::operator<<(std::ostream& out, const EncodingPair& rhs)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << rhs.pair.first << ':' << std::quoted(rhs.pair.second) << ')';
  return out;
}
std::pair< char, std::string > ibragimov::detail::getPair(const EncodingPair& rhs)
{
  return rhs.pair;
}
ibragimov::detail::EncodingPair ibragimov::detail::makeEncodingPair(const std::pair< char, std::string >& rhs)
{
  return EncodingPair{rhs};
}
