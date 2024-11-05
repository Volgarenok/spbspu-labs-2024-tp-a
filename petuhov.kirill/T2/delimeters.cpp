#include "delimeters.hpp"
#include <cctype>
#include <stdexcept>

std::istream &petuhov::operator>>(std::istream &in, petuhov::DelimiterIO &del) {
  char actual;
  in >> actual;

  if (actual != del.expected) {
    in.setstate(std::ios::failbit);
  }
  
  return in;
}

std::istream &petuhov::operator>>(std::istream &in, petuhov::UllLiteralIO &ull) {
  std::string input;
  in >> input;

  if (input.length() >= 2 && input[0] == '0' && (input[1] == 'x' || input[1] == 'X')) {
    try {
      ull.ref = std::stoull(input, nullptr, 16);
    } catch (const std::invalid_argument&) {
      in.setstate(std::ios::failbit);
    } catch (const std::out_of_range&) {
      in.setstate(std::ios::failbit);
    }
  } else if (input.length() > 1 && input[0] == '0') {
    try {
      ull.ref = std::stoull(input, nullptr, 8);
    } catch (const std::invalid_argument&) {
      in.setstate(std::ios::failbit);
    } catch (const std::out_of_range&) {
      in.setstate(std::ios::failbit);
    }
  } else {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream &operator>>(std::istream &in, petuhov::StringIO &str) {
  char ch;
  in >> ch;

  if (ch != '"') {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::string result;

  while (in.get(ch)) {
    if (ch == '"') {
      str.ref = result;
      return in;
    }
    result += ch;
  }
  
  in.setstate(std::ios::failbit);
  return in;
}
