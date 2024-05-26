#include "number_format.hpp"
#include <iostream>
#include <iomanip>
#include <map>

std::ostream & erohin::operator<<(std::ostream & output, NumberFormat && numformat)
{
  if (numformat.format == NUMBER)
  {
    output << numformat.number;
  }
  else if (numformat.format == PROPORTION)
  {
    output << numformat.number << " / " << numformat.size;
  }
  else if (numformat.format == FRACTIONAL)
  {
    output << std::setprecision(6) << std::fixed << static_cast< double >(numformat.number) / numformat.size;
  }
  else if (numformat.format == PERCENTAGE)
  {
    output << std::setprecision(6) << std::fixed << static_cast< double >(numformat.number) / numformat.size * 100 << " %";
  }
  return output;
}
