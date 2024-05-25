#ifndef CODE_WRAPPERS_HPP
#define CODE_WRAPPERS_HPP

#include <iosfwd>
#include <vector>

namespace ravinskij
{
  struct ReadWrapper
  {
    char &symbol;
    std::vector< bool > &code;
  };

  struct WriteWrapper
  {
    const char &symbol;
    const std::vector< bool > &code;
  };
 
  std::ostream& operator<<(std::ostream& out, WriteWrapper&& wrapper);
  std::istream& operator>>(std::istream& in, ReadWrapper&& wrapper);
}

#endif
