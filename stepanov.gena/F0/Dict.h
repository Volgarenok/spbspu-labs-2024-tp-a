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
    using TextMap = std::multimap<std::string, std::pair<size_t, size_t>>;
    using com1 = void(*)(std::map<std::string, TextMap>&, const std::string&, const std::string&);
    using com2 = void(*)(const std::map<std::string, TextMap>&, const std::string&, std::ostream&);
    using com3 = void(*)(std::map<std::string, TextMap>&, const std::string&, const std::string&, size_t);
    using com4 = void(*)(std::map<std::string, TextMap>&, const std::string&, const std::string&, const std::string&);
    using com5 = void(*)(std::map<std::string, TextMap>&, const std::string&);
    using com6 = void(*)(std::map<std::string, TextMap>&, const std::string&, const size_t&, const size_t&);
    using com7 = void(*)(const std::map<std::string, TextMap>&, const std::string&, const std::string&);

    std::map<std::string, com1> dict1_;
    std::map<std::string, com2> dict2_;
    std::map<std::string, com3> dict3_;
    std::map<std::string, com4> dict4_;
    std::map<std::string, com5> dict5_;
    std::map<std::string, com6> dict6_;
    std::map<std::string, com7> dict7_;
  };
}

#endif