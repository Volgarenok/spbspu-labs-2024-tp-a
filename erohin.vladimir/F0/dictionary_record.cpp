#include "dictionary_record.hpp"
#include <iostream>
#include <string>
#include "number_format.hpp"

erohin::Record::Record(const std::string & word_name, size_t word_number):
  word(word_name),
  number(word_number)
{}

erohin::Record::Record(const std::pair< std::string, size_t > & pair):
  Record(pair.first, pair.second)
{}

erohin::FormattedRecord::FormattedRecord(const Record & record, size_t word_number, numformat_t format):
  Record(record.word, record.number),
  total_number(word_number),
  numformat(format)
{}

std::istream & erohin::operator>>(std::istream & input, Record & record)
{
  return input >> record.word >> record.number;
}

std::ostream & erohin::operator<<(std::ostream & output, const Record & record)
{
  return output << record.word << " " << record.number;
}

std::ostream & erohin::operator<<(std::ostream & output, const FormattedRecord & record)
{
  return output << record.word << ": " << NumberFormat{ record.number, record.total_number, record.numformat };
}

erohin::Record erohin::createRecord(const std::pair< std::string, size_t > & pair)
{
  return Record(pair);
}

erohin::FormattedRecord erohin::createFormattedRecord(const Record & record, size_t total_number, numformat_t numformat)
{
  return FormattedRecord(record, total_number, numformat);
}
