#ifndef DELIMITER_I_HPP
#define DELIMITER_I_HPP

#include <string>

namespace sazanov
{
  struct DelimiterI
  {
    char expected;
  };

  struct StringDelimiterI
  {
    std::string expected;
  };

  struct VariableDelimiterI
  {
    char firstExpected;
    char secondExpected;
  };

  std::istream& operator>>(std::istream& in, DelimiterI&& exp);
  std::istream& operator>>(std::istream& in, StringDelimiterI&& exp);
  std::istream& operator>>(std::istream& in, VariableDelimiterI&& exp);
}

#endif //DELIMITER_I_HPP
