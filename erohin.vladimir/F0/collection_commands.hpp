#ifndef COLLECTION_COMMANDS_HPP
#define COLLECTION_COMMANDS_HPP

#include <iosfwd>
#include <map>
#include <string>
#include "number_format.hpp"

namespace erohin
{
  struct Record
  {
    std::string word;
    size_t number;
    size_t total_number;
    numformat_t numformat;
  };

  std::ostream & operator<<(std::ostream & output, const Record & record);
  Record convertToRecord(const std::pair< std::string, size_t > & pair, size_t total_number, numformat_t numformat);
  std::pair< std::string, size_t > convertToPair(std::string word, size_t number);
}

namespace erohin
{
  using dictionary = std::map< std::string, size_t >;
  using collection = std::map< std::string, dictionary >;

  void print_command(const collection & context, std::istream & input, std::ostream & output, numformat_t numformat);
}

#endif
