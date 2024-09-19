#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <algorithm>

#include "CrossRefs.hpp"

namespace stepanchenko
{
  void checkName(std::vector< CrossRefs > cross_refs, const std::string& name)
  {
    auto iter = std::find_if(cross_refs.begin(), cross_refs.end(), [&](const CrossRefs& cr) {
      return cr.getName() == name;
    });
    if (iter != cross_refs.end())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }

  bool isInIntersection(const CrossRefs& cr1, const CrossRefs& cr2);
}

#endif
