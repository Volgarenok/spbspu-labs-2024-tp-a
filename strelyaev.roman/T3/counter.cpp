#include "counter.hpp"

strelyaev::SeqCounter::SeqCounter(const std::vector< Point >& src):
        count_(0),
        src_(src)
      {}

size_t strelyaev::SeqCounter::operator()(const Polygon& plg)
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

size_t strelyaev::SeqCounter::operator()() const
{
  return count_;
}