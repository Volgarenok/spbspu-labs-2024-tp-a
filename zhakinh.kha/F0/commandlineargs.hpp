#ifndef COMMANDLINEARGS_HPP
#define COMMANDLINEARGS_HPP

#include <istream>
#include <ostream>
#include <map>
#include <functional>
#include "dictionary.hpp"

namespace zhakha
{
  using CommandFunction = std::function<void(std::istream&, std::ostream&, Dictionary&)>;
  using DictionaryMap = std::map< std::string, Dictionary >;
  void help(std::ostream& out);
  void check(std::istream& in, std::ostream& out, DictionaryMap& dicts);


  class CommandLineArgs
  {
  public:
    void addCommand(const std::string& command, CommandFunction function);
    void executeCommand(const std::string& command, std::istream& in, std::ostream& out, Dictionary& dicts);

  private:
    std::map<std::string, CommandFunction> commands_;
  };
}

#endif
