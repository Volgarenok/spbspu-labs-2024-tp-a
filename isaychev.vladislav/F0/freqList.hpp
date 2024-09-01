#ifndef FREQLISTVALUE_HPP
#define FREQLISTVALUE_HPP

#include <map>
#include <iosfwd>
#include "word.hpp"

namespace isaychev
{
  using value_t = std::pair< Word, size_t >;

  class FreqList
  {
   public:
    FreqList() = default;
    FreqList(const std::map< Word, size_t > & rhs);
    FreqList(std::map< Word, size_t > && rhs);

    size_t & at(const Word & rhs) noexcept;
    const size_t & at(const Word & rhs) const noexcept;
    void insert(const Word & rhs);
    void add_element(const value_t & rhs);

    size_t size() const noexcept;
    bool empty() const noexcept;
    const std::map< Word, size_t > & get_map() const noexcept;

   private:
    std::map< Word, size_t > list_;
  };

  std::ostream & operator<<(std::ostream & out, const FreqList & rhs);
  std::string convert_to_str(const value_t & rhs);
}

#endif
