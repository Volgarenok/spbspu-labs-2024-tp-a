#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "entities.hpp"

namespace ibragimov
{
  Encodings createEncodings(const DecodedText&);
  EncodedText encode(const DecodedText&, const Encodings&);
  DecodedText decode(const EncodedText&, const Encodings&);
  Encodings findEfficient(const std::vector< Encodings >&, const DecodedText&);
  Encodings findUnefficient(const std::vector< Encodings >&, const DecodedText&);
  std::vector< Encodings > compareEncodings(const std::vector< Encodings >&, const DecodedText&);
}

#endif
