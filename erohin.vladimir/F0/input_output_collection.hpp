#ifndef INPUT_OUTPUT_COLLECTION_HPP
#define INPUT_OUTPUT_COLLECTION_HPP

#include <map>
#include <string>
#include <iosfwd>

namespace erohin
{
  using dictionary = std::map< std::string, size_t >;
  using collection = std::map< std::string, dictionary >;

  void inputCollection(collection & context, std::istream & input);
  void outputCollection(const collection & context, std::ostream & output);
}

#endif
