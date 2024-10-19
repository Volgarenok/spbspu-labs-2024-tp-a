#include "Keys.hpp"
#include "Delimiter.hpp"
#include "StreamGuard.hpp"

std::istream &vorobieva::operator>>(std::istream &in, ComplexKey &&key) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  using del = DelimiterChar;
  using delStr = DelimiterString;
  double real = 0;
  double imag = 0;

  in >> delStr{"#c("} >> real >> imag >> del{')'};

  if (in) {
    key.smth = {real, imag};
  }

  return in;
}

std::istream &vorobieva::operator>>(std::istream &in, BinaryKey &&key) {
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  StreamGuard fmtguard(in);
  using del = DelimiterChar;
  in >> del{'0'} >> del{'b'};

  std::string s = "";
  std::getline(in, s, ':');

  for (size_t i = 0; i < s.size(); ++i) {
    if (s[i] != '0' && s[i] != '1') {
      s.resize(i);
      break;
    }
  }

  unsigned long long result = 0;
  int power = -1;

  for (size_t i = 0; i < s.size(); i++) {
    if (s[s.size() - i] == '1') {
      result += std::pow(2, power);
      power++;
    }
  }

  key.smth = result;

  return in;
}

std::ostream &vorobieva::operator<<(std::ostream &out, BinaryKey &&key) {
  unsigned long long num = key.smth;
  int power = -1;

  while (num > std::pow(2, power)) {
    power++;
  }

  while (power >= 0) {
    if (num >= std::pow(2, power)) {
      out << 1;
      num -= std::pow(2, power);
      power--;
    } else {
      out << 0;
      power--;
    }
  }

  return out;
}

std::istream &vorobieva::operator>>(std::istream &in, StringKey &&key) {
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }

  using del = DelimiterChar;
  in >> del{'"'};
  std::getline(in, key.smth, '\"');
  return in;
}
