#ifndef COLLECTION_COMMANDS_HPP
#define COLLECTION_COMMANDS_HPP

#include <iosfwd>
#include <map>
#include <string>
#include "number_format.hpp"

namespace erohin
{
  using dictionary = std::map< std::string, size_t >;
  using collection = std::map< std::string, dictionary >;

  void printCommand(const collection & context, std::istream & input, std::ostream & output, numformat_t numformat);
}

#endif
