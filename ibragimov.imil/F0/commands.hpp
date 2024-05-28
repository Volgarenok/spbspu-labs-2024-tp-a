#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "entities.hpp"

namespace ibragimov
{
  ibragimov::Encodings createEncodings(const DecodedText&);
  ibragimov::EncodedText encode(const DecodedText&, const Encodings&);
  ibragimov::DecodedText decode(const EncodedText&, const Encodings&);
}

#endif
