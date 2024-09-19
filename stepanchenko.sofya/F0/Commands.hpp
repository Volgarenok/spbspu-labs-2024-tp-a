#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>
#include <string>

namespace stepanchenko
{
  class CrossRefs
  {
  public:
    CrossRefs() = default;
    ~CrossRefs() = default;
    CrossRefs(const CrossRefs& other) = default;
    CrossRefs(CrossRefs&& moved) noexcept = default;
  private:
    std::unordered_map< std::string, std::list< size_t > > table_;
    std::vector< std::string > lines_;
    std::string name_;
  }
}

#endif
