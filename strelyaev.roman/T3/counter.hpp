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
      SeqCounter(const std::vector< Point >& src):
        count_(0),
        src_(src)
      {}

      size_t operator()(const Polygon& plg)
      {
        if (plg.points == src_)
        {
          count_++;
        }
        else
        {
          count_ = 0;
        }
        return count_;
      }
      
    private:
      size_t count_;
      const std::vector< Point > src_;
  };
}

#endif
