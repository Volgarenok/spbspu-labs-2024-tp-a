#ifndef _DICTIONARY_HPP
#define _DICTIONARY_HPP

#include <set>
#include <string>
#include <memory>
#include <map>

namespace kornienko
{
  class Dictionary
  {
  public:
    Dictionary() = default;
    ~Dictionary() = default;
  private:
    std::map< std::string, std::shared_ptr< std::set< std::string > > > dictionary_;
  };
}

#endif
