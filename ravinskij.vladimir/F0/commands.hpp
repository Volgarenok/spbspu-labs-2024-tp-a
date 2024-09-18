#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <map>
#include <list>
#include <string>
#include <vector>
#include "node.hpp"

namespace ravinskij
{
  using traverserTable = std::map< std::string, std::list< nodePtr > >;
  using fileTable = std::map< std::string, std::string >;
  using encodeMap = std::map< char, std::vector< bool > >;
  using encodesTable = std::map< std::string, encodeMap >;

  void printHelp(std::ostream&);

  void addText(std::istream&, fileTable&);
  void saveText(std::istream&, fileTable&);
  void deleteText(std::istream&, fileTable&);
  void printText(std::istream&, std::ostream&, const fileTable&);

  void createEncoding(std::istream&, encodesTable&, traverserTable&, const fileTable&);
  void deleteEncoding(std::istream&, encodesTable&, traverserTable&);
  void encode(std::istream&, const encodesTable&, fileTable&);
  void decode(std::istream&, const traverserTable&, fileTable&);
  void addEncoding(std::istream&, encodesTable&, traverserTable&);
  void saveEncoding(std::istream&, const encodesTable&, const traverserTable&);

  void compareEncodings(std::istream&, std::ostream&, const fileTable&, const encodesTable&);
  void printFiles(std::istream&, std::ostream&, const fileTable&);
  void printTexts(std::istream&, std::ostream&, const fileTable&);
  void printAll(std::istream&, std::ostream&, const fileTable&);
}

#endif
