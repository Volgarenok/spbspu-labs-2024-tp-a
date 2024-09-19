#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>
#include <string>
#include <iterator>

namespace stepanchenko
{
  class CrossRefs
  {
  public:
    CrossRefs() = default;
    ~CrossRefs() = default;
    CrossRefs(const CrossRefs& other) = default;
    CrossRefs(CrossRefs&& moved) noexcept = default;

    std::unordered_map<std::string, std::list< size_t > >::iterator begin();
    std::unordered_map<std::string, std::list< size_t > >::iterator end();
    std::unordered_map<std::string, std::list< size_t > >::const_iterator search(const std::string& word) const;

  private:
    std::unordered_map< std::string, std::list< size_t > > table_;
    std::vector< std::string > lines_;
    std::string name_;
  }
}

#endif
