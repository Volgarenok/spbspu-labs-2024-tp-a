#include "Commands.hpp"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using Dict = std::map< std::string, std::vector< std::string> >;
using allDicts = std::vector< Dict >;

void addWord(std::istream& in, allDicts& dicts) {}
void addTranslation(std::istream& in, allDicts& dicts) {}

void searchWord(std::istream& in, std::ostream& out, const allDicts& dicts) {}
void searchTranslation(std::istream& in, std::ostream& out, const allDicts& dicts) {}

void deleteWord(std::istream& in, allDicts& dicts) {}
void deleteTranslation(std::istream& in, allDicts& dicts) {}

void findSynonyms(std::istream& in, std::ostream& out, const allDicts& dicts) {}
void countWords(std::istream& in, std::ostream& out, const allDicts& dicts) {}

void intersect(std::istream& in, allDicts& dicts) {}
void subtract(std::istream& in, allDicts& dicts) {}
void merge(std::istream& in, allDicts& dicts) {}
