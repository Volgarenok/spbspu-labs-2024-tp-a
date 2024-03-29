#ifndef DELIMITER_HPP
#define DELIMITER_HPP
namespace sakovskaia
{
  struct delimiter_t
  {
    char expected;
  };
  std::istream & operator>>(std::istream & input, delimiter_t && exp);
}
#endif
