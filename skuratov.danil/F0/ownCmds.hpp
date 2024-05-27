#ifndef OWN_CMDS_HPP
#define OWN_CMDS_HPP

#include <iostream>

namespace skuratov
{
  void help(std::ostream& out);
  void load();
  void huff();
  void compress();
  void save();
  void loadEncoded();
  void decompress();
  void eff();
  void sortData();
  void removeDuplicates();
  void countWords();

}

#endif
