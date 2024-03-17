#ifndef STREAM_GUARD
#define STREAM_GUARD

#include<ios>

namespace zaparin
{
  class StreamGuard
  {
  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;

  public:
    StreamGuard(std::basic_ios<char>& s);
    ~StreamGuard();
  };
}

#endif