#ifndef DICTIONARY_RECORD_HPP
#define DICTIONARY_RECORD_HPP

#include <iosfwd>
#include <string>
#include "number_format.hpp"

namespace erohin
{
  struct Record
  {
    std::pair< std::string, size_t > data;
    Record();
    Record(const std::pair< std::string, size_t > & pair);
  };

  struct FormattedRecord: Record
  {
    size_t total_number;
    numformat_t numformat;
    FormattedRecord();
    FormattedRecord(const Record & record, size_t word_number, numformat_t format);
  };

  std::istream & operator>>(std::istream & input, Record & record);
  std::ostream & operator<<(std::ostream & output, const Record & record);
  std::ostream & operator<<(std::ostream & output, const FormattedRecord & record);
  Record createRecord(const std::pair< std::string, size_t > & pair);
  FormattedRecord createFormattedRecord(const Record & record, size_t total_number, numformat_t numformat);
}

#endif
