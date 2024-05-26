#ifndef COLLECTION_COMMANDS_HPP
#define COLLECTION_COMMANDS_HPP

#include <iosfwd>
#include <map>
#include <string>
#include "input_output_collection.hpp"
#include "number_format.hpp"

namespace erohin
{
  void printCommand(const collection & context, std::istream & input, std::ostream & output, numformat_t numformat);
}

#endif
