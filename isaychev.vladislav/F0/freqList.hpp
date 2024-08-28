#ifndef FREQLISTVALUE_HPP
#define FREQLISTVALUE_HPP

#include <map>
#include <iosfwd>
#include "word.hpp"

namespace isaychev
{
  class FreqList
  {
   public:
    size_t & at(const Word & rhs) noexcept;
    const size_t & at(const Word & rhs) const noexcept;
    void insert(const Word & rhs);
    void add_element(const std::pair< Word, size_t > & rhs);

    size_t size() const noexcept;
    bool empty() const noexcept;
    const std::map< Word, size_t > & get_map() const noexcept;

   private:
    std::map< Word, size_t > list;
  };

  std::ostream & operator<<(std::ostream & out, const FreqList & rhs);
  std::string convert_to_str(const std::pair< Word, size_t > & rhs);
}

#endif
