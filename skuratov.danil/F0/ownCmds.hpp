#ifndef OWN_CMDS_HPP
#define OWN_CMDS_HPP

#include <iostream>
#include <fstream>

namespace skuratov
{
  void help(std::ostream& out);

  void load(std::istream& in, std::ostream& out);
  void huff(std::istream& in, std::ostream& out);
  void compress(std::istream& in, std::ostream& out);
  void save(std::istream& in, std::ostream& out);
  void loadEncoded(std::istream& in, std::ostream& out);
  void decompress(std::istream& in, std::ostream& out);
  void eff(std::istream& in, std::ostream& out);
  void sortData(std::istream& in, std::ostream& out);
  void removeDuplicates(std::istream& in, std::ostream& out);
  void countWords(std::istream& in, std::ostream& out);
}

#endif
