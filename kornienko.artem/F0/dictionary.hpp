#ifndef _DICTIONARY_HPP
#define _DICTIONARY_HPP

#include <vector>
#include <string>
#include <map>

namespace kornienko
{
  struct Dictionary
  {
  public:
    std::map< std::string, std::vector< std::string > > dictionary_;
  };
}

#endif
