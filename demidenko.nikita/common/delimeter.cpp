#include "delimeter.hpp"

template <>
void demidenko::DelimeterI::parse(std::istream& in)
{
  char current_character = ' ';
  const char* delimeter = data;
  while (in && *delimeter)
  {
    in >> current_character;
    if (*delimeter != current_character)
    {
      in.setstate(std::ios::failbit);
      return;
    }
    ++delimeter;
  }
}
