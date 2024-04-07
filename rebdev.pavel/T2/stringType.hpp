#ifndef STRINGTYPE_HPP
#define STRINGTYPE_HPP

#include <iostream>
#include <string>

namespace rebdev
{
  struct stringType
  {
    std::string data_;

    bool operator==(const stringType & str) const noexcept;
    bool operator<(const stringType & str) const noexcept;
  };

  std::istream & operator>>(std::istream & in, stringType & str);
  std::ostream & operator<<(std::ostream & out, const stringType & str);
}

#endif

