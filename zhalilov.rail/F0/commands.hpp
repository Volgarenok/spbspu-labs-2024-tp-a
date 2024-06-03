#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <map>
#include <list>

#include "expressionTokens.hpp"

namespace zhalilov
{
  using varModule = std::map< std::string, std::list< InfixToken > >;
  using modulesMap = std::map< std::string, varModule >;
  void calc(const modulesMap &, const std::string &, std::istream &, std::ostream &);
  void modulesadd(modulesMap &, std::istream &, std::ostream &);
  void modulesvaradd(modulesMap &, std::istream &, std::ostream &);

  void modulesdelete(modulesMap &, std::istream &, std::ostream &);
  void modulesvardelete(modulesMap &, std::istream &, std::ostream &);

  void modulesshow(const modulesMap &, std::istream &, std::ostream &);

  void modulesimport(modulesMap &, std::istream &, std::ostream &);
  void modulesexport(const modulesMap &, std::istream &, std::ostream &);

  void historyshow(const std::string &, std::istream &, std::ostream &);
  void historyclear(const std::string &, std::istream &, std::ostream &);
}

#endif
