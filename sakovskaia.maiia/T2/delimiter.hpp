#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <istream>
namespace sakovskaia
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & input, Delimiter && exp);
}
#endif
