#ifndef ENTITIES_HPP
#define ENTITIES_HPP

#include <istream>
#include <map>
#include <string>

namespace ibragimov
{
  struct Entity
  {
    Entity() = default;
    virtual ~Entity() = default;
    virtual void outputInfo() = 0;
  };
  struct Encodings: Entity
  {
    Encodings() = default;
    explicit Encodings(const std::map< char, std::string >&);
    Encodings(const Encodings&) = default;
    Encodings& operator=(const Encodings&) = default;
    ~Encodings() override = default;

    void outputInfo() override;

    std::map< char, std::string > encodingTable;
  };
  std::istream& operator>>(std::istream&, Encodings&);
  std::ostream& operator<<(std::ostream&, const Encodings&);
  struct DecodedText: Entity
  {
    DecodedText() = default;
    explicit DecodedText(const std::string&);
    DecodedText(const DecodedText&) = default;
    DecodedText& operator=(const DecodedText&) = default;
    ~DecodedText() override = default;

    void outputInfo() override;

    std::string text;
    size_t size;
    size_t bits;
  };
  std::istream& operator>>(std::istream&, DecodedText&);
  std::ostream& operator<<(std::ostream&, const DecodedText&);
  struct EncodedText: Entity
  {
    EncodedText() = default;
    explicit EncodedText(const std::string&);
    EncodedText(const EncodedText&) = default;
    EncodedText& operator=(const EncodedText&) = default;
    ~EncodedText() override = default;

    void outputInfo() override;

    std::string text;
    size_t size;
    size_t bits;
  };
  std::istream& operator>>(std::istream&, EncodedText&);
  std::ostream& operator<<(std::ostream&, const EncodedText&);
}

#endif
