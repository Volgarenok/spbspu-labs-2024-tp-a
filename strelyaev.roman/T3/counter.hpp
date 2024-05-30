#ifndef COUNTER_HPP
#define COUNTER_HPP
#include <stddef.h>
#include <vector>
#include "polygon.hpp"

namespace strelyaev
{
  struct SeqCounter
  {
    public:
      SeqCounter(const std::vector< Point >& src);
      size_t operator()(const Polygon& plg);
      size_t operator()() const;

    private:
      size_t count_;
      size_t max_seq_count_;
      const std::vector< Point > src_;
  };
}

#endif
