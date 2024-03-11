#include "delimiter.hpp"

std::istream& ibragimov::operator>>(std::istream& in, Delimiter&& expectation)
{
  std::istream::sentry guard(in);
  if (guard)
  {
    char c = 0;
    for (size_t i = 0; expectation.expected[i] != '\0'; ++i) {
      in >> c;
      if (c != expectation.expected[i]) {
        in.setstate(std::ios::failbit);
      }
    }
  }
  return in;
}
