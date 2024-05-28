#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include "entities.hpp"

namespace ibragimov
{
  ibragimov::Encodings createEncodings(const DecodedText&);
  ibragimov::EncodedText encode(const DecodedText&, const Encodings&);
  ibragimov::DecodedText decode(const EncodedText&, const Encodings&);
  ibragimov::Encodings findEfficient(const std::vector< Encodings >&, const DecodedText&);
  ibragimov::Encodings findUnefficient(const std::vector< Encodings >&, const DecodedText&);
}

#endif
