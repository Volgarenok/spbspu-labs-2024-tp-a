#ifndef OWN_CMDS_HPP
#define OWN_CMDS_HPP

#include <iostream>
#include <fstream>
#include "huffmanCoding.hpp"

namespace skuratov
{
  void help(std::ostream& out);

  void load(std::istream& in, std::ostream& out, Context& context);
  void huff(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext);
  void compress(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext);
  void save(std::istream& in, std::ostream& out, const Context& context);
  void loadEncoded(std::istream& in, std::ostream& out, Context& context);
  void decompress(std::istream& in, std::ostream& out, Context& context, CodeContext& codeContext);
  void eff(std::istream& in, std::ostream& out, const Context& context, const CodeContext& codeContext);
  void sortData(std::istream& in, std::ostream& out, Context& context);
  void removeDuplicates(std::istream& in, std::ostream& out, Context& context);
  void countWords(std::istream& in, std::ostream& out, const Context& context);
}

#endif
