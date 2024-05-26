#ifndef DICTIONARY_RECORD_HPP
#define DICTIONARY_RECORD_HPP

#include <iosfwd>
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
}

#endif
