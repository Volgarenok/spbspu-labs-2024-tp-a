#ifndef STREAMGUARD_H
#define STREAMGUARD_H

#include <iostream>
#include <iomanip>


class StreamGuard
{
  public:
    StreamGuard(std::ios& stream);
    ~StreamGuard();

  private:
    std::ios& stream_;
    std::ios::fmtflags state_;
    std::streamsize precision_;
    char fill_;
};

#endif
