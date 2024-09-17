#ifndef SET_HPP
#define SET_HPP
#include <map>
#include <string>
#include <vector>

namespace zolotukhin
{
  struct Set
  {
    std::map<std::string, std::vector<std::string>> set_;
  };
}
#endif
