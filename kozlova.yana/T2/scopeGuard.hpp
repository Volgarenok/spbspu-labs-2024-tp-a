#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <ios>

namespace kozlova
{
  class ScopeGuard
  {
  public:
    ScopeGuard(std::basic_ios< char >& s);
    ~ScopeGuard();

  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}
#endif
