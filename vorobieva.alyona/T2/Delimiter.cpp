#include "Delimiter.hpp"

std::istream &vorobieva::operator>>(std::istream &in, DelimiterChar &&exp) {
  std::istream::sentry guard(in);

  if (!guard) {
    return in;
  }

  char c = '0';
  in >> c;
  c = std::tolower(c);

  if (in && (c != exp.expected)) {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream &vorobieva::operator>>(std::istream &in, DelimiterString &&exp) {
  std::istream::sentry guard(in);

  if (!guard) {
    return in;
  }
  for (size_t i = 0; exp.expected[i] != '\0'; ++i) {
    in >> DelimiterChar{exp.expected[i]};
  }

  return in;
}
