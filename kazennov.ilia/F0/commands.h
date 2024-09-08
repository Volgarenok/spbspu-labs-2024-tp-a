#ifndef COMMANDS_H
#define COMMANDS_H

#include "dictionary.h"

namespace kazennov
{
  void add_word(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts);
  void add_from_file(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts);
  void get_frequency(std::istream& in, std::ostream& out, std::map<std::string, FrequencyDict>& mapOfDicts);
  void delete_word(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts);
  void delete_dictionary(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts);
  void output(std::istream& in, std::ostream& out, std::map<std::string, FrequencyDict>& mapOfDicts);
  void get_word_with_highest_frequency(std::istream& in, std::ostream& out, std::map<std::string, FrequencyDict>& mapOfDicts);
  void get_count_of_word(std::istream& in, std::ostream& out, std::map<std::string, FrequencyDict>& mapOfDicts);
  void intersection(std::istream& in, std::map<std::string, FrequencyDict>& mapOfDicts);
}
#endif


