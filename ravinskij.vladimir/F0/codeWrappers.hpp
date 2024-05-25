#ifndef CODE_WRAPPERS_HPP
#define CODE_WRAPPERS_HPP

#include <iosfwd>
#include <vector>

namespace ravinskij
{
  struct ReadWrapper
  {
    char& symbol;
    std::vector< bool >& code;
    size_t& frequency;
  };

  struct WriteWrapper
  {
    const char& symbol;
    const std::vector< bool >& code;
    const size_t& frequency;
  };

  std::ostream& operator<<(std::ostream& out, WriteWrapper&& wrapper);
  std::istream& operator>>(std::istream& in, ReadWrapper&& wrapper);
}

#endif
