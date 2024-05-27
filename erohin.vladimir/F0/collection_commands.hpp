#ifndef COLLECTION_COMMANDS_HPP
#define COLLECTION_COMMANDS_HPP

#include <iosfwd>
#include <map>
#include <string>
#include "input_output_collection.hpp"
#include "number_format.hpp"

namespace erohin
{
  using texts_source = std::map< std::string, std::string >;

  void addTextCommand(texts_source & context, std::istream & input, std::ostream &);
  void createDictCommand(collection & dict_context, const texts_source & text_context, std::istream & input, std::ostream &);
  void printCommand(const collection & context, std::istream & input, std::ostream & output, numformat_t numformat);
}

#endif
