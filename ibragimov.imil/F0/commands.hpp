#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <vector>
#include "entities.hpp"

namespace ibragimov
{
  Encodings inputEncodings(std::istream&);
  DecodedText inputDecodedText(std::istream&);
  EncodedText inputEncodedText(std::istream&);
  void outputEncodings(std::ostream&, const Encodings&);
  void outputDecodedText(std::ostream&, const DecodedText&);
  void outputEncodedText(std::ostream&, const EncodedText&);

  Encodings createEncodings(const DecodedText&);
  EncodedText encode(const DecodedText&, const Encodings&);
  DecodedText decode(const EncodedText&, const Encodings&);

  Encodings findEfficient(const std::vector< Encodings >&, const DecodedText&);
  Encodings findUnefficient(const std::vector< Encodings >&, const DecodedText&);
  std::vector< Encodings > compareEncodings(const std::vector< Encodings >&, const DecodedText&);
}

#endif
