#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP
#include <ios>

namespace lazareva {
  struct StreamGuard {
  public:
    explicit StreamGuard(std::basic_ios<char>& s) : s_(s), precision_(s.precision()), flags_(s.flags()) { }

    ~StreamGuard() {
      s_.precision(precision_);
      s_.flags(flags_);
    }

  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
  };
}
#endif
