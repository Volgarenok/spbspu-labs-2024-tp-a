#include "parsescientific.hpp"

std::ostream& gladyshev::parseScientific(std::ostream& out, double key)
{
  int exponent = 0;
  while (key >= 10)
  {
    key /= 10;
    ++exponent;
  }
  while (key < 1)
  {
    key *= 10;
    --exponent;
  }
  out << key << 'e' << exponent;
}
