#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm>
#include <iostream>
#include <utility>

#include "CrossRefs.hpp"

namespace stepanchenko
{
  std::vector<CrossRefs> createCrossRefsFromFile(std::istream& fin);
  void checkName(std::vector< CrossRefs >& cross_refs, const std::string& name);
  void printL(const std::pair < size_t, std::string >& line, std::ostream& out);
  void writeToFile(const std::string& name, const std::vector< std::pair< size_t, std::string > >& lines, std::ofstream& file);
  void swapLines(const std::vector< std::pair< size_t, std::string > >::iterator first,
    const std::vector< std::pair< size_t, std::string > >::iterator second, bool pred);
  bool isInIntersection(std::pair <std::string, std::list< size_t > > entry, CrossRefs& cr);
  void helpCmd(std::ostream& out);
}

#endif
