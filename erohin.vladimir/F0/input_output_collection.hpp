#ifndef INPUT_OUTPUT_COLLECTION_HPP
#define INPUT_OUTPUT_COLLECTION_HPP

#include <map>
#include <string>
#include <iosfwd>
#include "dictionary.hpp"

namespace erohin
{
  using collection = std::map< std::string, Dictionary >;

  void inputCollection(collection & dict_context, std::istream & input);
  void outputCollection(const collection & dict_context, std::ostream & output);
}

#endif
