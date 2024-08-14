#include "dictionary_record.hpp"
#include <iostream>
#include <string>
#include "format.hpp"
#include "delimiter.hpp"
#include "number_format.hpp"

erohin::Record::Record():
  data(std::make_pair("", 0))
{}

erohin::Record::Record(const std::pair< std::string, size_t > & pair):
  data(pair)
{}

erohin::FormattedRecord::FormattedRecord():
  Record(),
  total_number(0),
  numformat(NUMBER)
{}

erohin::FormattedRecord::FormattedRecord(const Record & record, size_t word_number, numformat_t format):
  Record(record.data),
  total_number(word_number),
  numformat(format)
{}

std::istream & erohin::operator>>(std::istream & input, Record & record)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return input >> StringFormat{ record.data.first, '"' } >> record.data.second;
}

std::ostream & erohin::operator<<(std::ostream & output, const Record & record)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  return output << "\"" << record.data.first << "\" " << record.data.second;
}

std::ostream & erohin::operator<<(std::ostream & output, const FormattedRecord & record)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  return output << record.data.first << ": " << NumberFormat{ record.data.second, record.total_number, record.numformat };
}

erohin::FormattedRecord erohin::createFormattedRecord(const Record & record, size_t total_number, numformat_t numformat)
{
  return FormattedRecord(record, total_number, numformat);
}
