#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <ios>

namespace ravinskij
{
  class ScopeGuard
  {
  public:
    ScopeGuard(std::basic_ios< char >& stream);
    ~ScopeGuard();

  private:
    std::basic_ios< char >& stream_;
    std::basic_ios< char >::fmtflags flags_;
    std::streamsize precision_;
  };

}
#endif
