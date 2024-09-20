#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "dictionary.hpp"

namespace lebedev
{
  using dicts_t = std::map< std::string, Dictionary >;
  void doHelp(std::ostream & output);
  void getReadtextCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getFindCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getDeleteCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getPrinttopnCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getPrintantitopnCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getPrintCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getMergeCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getUnionCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getExpandCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getSearchfreqCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getSaveCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
  void getReaddictCmd(dicts_t & dictionaries, std::istream & input, std::ostream & output);
}

#endif
