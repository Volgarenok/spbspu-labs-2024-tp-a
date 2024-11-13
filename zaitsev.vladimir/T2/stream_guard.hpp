#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP
#include <ios>

namespace zaitsev
{
  class StreamGuard {
  public:
    StreamGuard(std::basic_ios< char >& stream);
    ~StreamGuard();
  private:
    std::basic_ios< char >& stream_;
    std::basic_ios< char >::fmtflags flags_;
  };
}
#endif
