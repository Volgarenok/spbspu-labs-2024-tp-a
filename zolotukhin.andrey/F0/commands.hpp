#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "AVLTree.hpp"

namespace zolotukhin
{
  void create(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void addWord(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void removeWord(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void search(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void display(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void countWords(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void clearSet(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void mergeSets(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
  void intersectSets(std::map<std::string, Set>& Sets, std::istream& inp, std::ostream& out);
}
#endif
