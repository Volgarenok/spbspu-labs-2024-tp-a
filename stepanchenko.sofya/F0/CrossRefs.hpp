#ifndef CROSS_REFS_HPP
#define CROSS_REFS_HPP

#include <unordered_map>
#include <string>
#include <forward_list>

namespace stepanchenko
{
  class CrossRefs
  {
  public:
  private:
    std::unordered_map< std::string, std::forward_list< size_t > > table_;
  };
}

#endif
