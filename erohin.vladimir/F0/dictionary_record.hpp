#ifndef DICTIONARY_RECORD_HPP
#define DICTIONARY_RECORD_HPP

#include <iosfwd>
#include <string>
#include <utility>
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
  FormattedRecord createFormattedRecord(const Record & record, size_t total_number, numformat_t numformat);
  template< class T1, class T2 >
  Record createRecord(const std::pair< T1, T2 > & pair)
  {
    return Record(std::make_pair(std::get< std::string >(pair), std::get< size_t >(pair)));
  }
}

#endif
