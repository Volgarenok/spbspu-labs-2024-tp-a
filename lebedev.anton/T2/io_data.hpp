#ifndef IO_DATA_HPP
#define IO_DATA_HPP

#include <iostream>
#include <string>

namespace lebedev
{
  struct DoubleLit
  {
    double & data;
  };
  struct DoubleLitOut
  {
    double data;
  };
  struct DoubleSci
  {
    double & data;
  };
  struct DoubleSciOut
  {
    double data;
  };
  struct String
  {
    std::string & data;
  };

  std::istream & operator>>(std::istream & input, DoubleLit && dbl_lit);
  std::ostream & operator<<(std::ostream & output, const DoubleLitOut && dbl_lit);
  std::istream & operator>>(std::istream & input, DoubleSci && dbl_sci);
  std::ostream & operator<<(std::ostream & output, const DoubleSciOut && dbl_sci);
  std::istream & operator>>(std::istream & input, String && str);
}

#endif
