#include "dictionary_record.hpp"
#include <iostream>
#include <string>
#include "number_format.hpp"

std::ostream & erohin::operator<<(std::ostream & output, const Record & record)
{
  return output << record.word << ": " << NumberFormat{ record.number, record.total_number, record.numformat };
}

erohin::Record erohin::convertToRecord(const std::pair< std::string, size_t > & pair, size_t total_number, numformat_t numformat)
{
  return std::move(Record{ pair.first, pair.second, total_number, numformat });
}
