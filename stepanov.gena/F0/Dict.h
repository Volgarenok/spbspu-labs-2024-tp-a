#ifndef DICT_H
#define DICT_H

#include <string>
#include <map>
#include "Commands.h"

namespace stepanov
{
  class Commands
  {
  public:
    Commands();
    void runCommand(std::istream& in, std::ostream& out);

  private:
    using com1 = void(*)(std::map<std::string, TextMap>&, const std::string&, const std::string&);
    using com2 = void(*)(const std::map<std::string, TextMap>&, const std::string&, std::ostream&);
    using com3 = void(*)(std::map<std::string, TextMap>&, const std::string&, const std::string&, size_t);
    using com4 = void(*)(std::map<std::string, TextMap>&, const std::string&, const std::string&, const std::string&);
    using com5 = void(*)(std::map<std::string, TextMap>&, const std::string&, const std::string&);
    using com6 = void(*)(std::map<std::string, TextMap>&, const std::string&, const size_t&, const size_t&);

    std::map<std::string, com1> dict1_; // input, output, add, remove, deleteMap
    std::map<std::string, com2> dict2_; // output
    std::map<std::string, com3> dict3_; // addLine
    std::map<std::string, com4> dict4_; // merge, intersection, substract
    std::map<std::string, com5> dict5_; // delByWord, change
    std::map<std::string, com6> dict6_; // swapStr
  };
}

#endif