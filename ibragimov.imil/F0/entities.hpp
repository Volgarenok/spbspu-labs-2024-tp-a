#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <map>
#include <string>

namespace ibragimov
{
  struct Encodings
  {
    Encodings() = delete;
    Encodings(const std::map< char, std::string >&);
    ~Encodings() = default;

    std::map< char, std::string > encodingTable;
  };
  struct DecodedText
  {
    DecodedText() = delete;
    DecodedText(const std::string&);
    ~DecodedText() = default;

    std::string text;
    size_t size;
  };
  struct EncodedText
  {
    EncodedText() = delete;
    EncodedText(const std::string&);
    ~EncodedText() = default;

    std::string text;
    size_t size;
  };
}

#endif
