#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <ostream>
#include "dictionary.hpp"

namespace nikitov
{
  void printDictCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void printAllCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);

  void findTranslationCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void findAntonymCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);

  void translateSentenceCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void translateFileCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);

  void saveCmd(const std::map< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&);

  void createCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void addTranslationCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void addAntonymCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void editPrimaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void editSecondaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void deletePrimaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void deleteSecondaryCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void deleteAntonymCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void mergeCmd(std::map< std::string, Dictionary >& dictOfDicts, std::istream& input);
}
#endif