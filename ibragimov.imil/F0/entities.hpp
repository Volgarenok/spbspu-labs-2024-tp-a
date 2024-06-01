#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <istream>
#include <map>
#include <string>

namespace ibragimov
{
  struct Encodings
  {
    Encodings() = delete;
    explicit Encodings(const std::map< char, std::string >&);
    Encodings(const Encodings&) = default;
    Encodings& operator=(const Encodings&) = default;
    ~Encodings() = default;

    std::map< char, std::string > encodingTable;
  };
  std::istream& operator>>(std::istream&, Encodings&);
  std::ostream& operator<<(std::ostream&, const Encodings&);
  struct DecodedText
  {
    DecodedText() = delete;
    explicit DecodedText(const std::string&);
    DecodedText(const DecodedText&) = default;
    DecodedText& operator=(const DecodedText&) = default;
    ~DecodedText() = default;

    std::string text;
    size_t size;
    size_t bits;
  };
  std::istream& operator>>(std::istream&, DecodedText&);
  std::ostream& operator<<(std::ostream&, const DecodedText&);
  struct EncodedText
  {
    EncodedText() = delete;
    explicit EncodedText(const std::string&);
    EncodedText(const EncodedText&) = default;
    EncodedText& operator=(const EncodedText&) = default;
    ~EncodedText() = default;

    std::string text;
    size_t size;
    size_t bits;
  };
  std::istream& operator>>(std::istream&, EncodedText&);
  std::ostream& operator<<(std::ostream&, const EncodedText&);
}

#endif
