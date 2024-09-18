#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP
#include <ios>

namespace kozlova
{
  class ScopeGuard
  {
  public:
    explicit ScopeGuard(std::basic_ios< char > &);
    ~ScopeGuard();

  private:
    std::basic_ios< char > & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags flags_;
  };
}
#endif
