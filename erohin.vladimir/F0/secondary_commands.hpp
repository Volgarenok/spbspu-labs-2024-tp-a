#ifndef SECONDARY_COMMAND_HPP
#define SECONDARY_COMMAND_HPP

#include <iosfwd>

namespace erohin
{
  void printHelp(std::ostream & output);
  void checkDictionary(const char * file_name, std::ostream & output);
}

#endif
