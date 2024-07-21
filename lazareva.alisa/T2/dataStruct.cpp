#include "dataStruct.hpp"
#include "delimiter.hpp"
#include "streamGuard.hpp"
#include <iomanip>
#include <iostream>

namespace lazareva {

// Определение оператора >> для double
std::istream& operator>>(std::istream& in, double& value) {
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }
  StreamGuard s_guard(in);
  std::operator>>(in, value); // Используем std::operator>> для ввода double
  in >> Delimiter{'d'};
  return in;
}

// Определение оператора >> для long long
std::istream& operator>>(std::istream& in, long long& value) {
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }
  StreamGuard s_guard(in);
  std::operator>>(in, value); // Используем std::operator>> для ввода long long
  in >> Delimiter{'l'} >> Delimiter{'l'};
  return in;
}

// Определение оператора >> для std::string
std::istream& operator>>(std::istream& in, std::string& value) {
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }
  StreamGuard s_guard(in);
  in >> Delimiter{'"'};
  std::getline(in, value, '"');
  return in;
}

// Определение оператора >> для DataStruct
std::istream& operator>>(std::istream& in, DataStruct& data) {
  std::istream::sentry guard(in);
  if (!guard) {
    return in;
  }
  StreamGuard s_guard(in);
  in >> Delimiter{'('};

  for (int i = 0; i < 3; ++i) {
    in >> Delimiter{':'} >> Delimiter{'k'} >> Delimiter{'e'} >> Delimiter{'y'};
    int keyIndex;
    in >> keyIndex;

    switch (keyIndex) {
      case 1:
        std::operator>>(in, data.key1); // Используем std::operator>> для ввода в data.key1
        break;
      case 2:
        std::operator>>(in, data.key2); // Используем std::operator>> для ввода в data.key2
        break;
      case 3:
        std::operator>>(in, data.key3); // Используем std::operator>> для ввода в data.key3
        break;
      default:
        in.setstate(std::ios::failbit);
        break;
    }
  }

  in >> Delimiter{':'} >> Delimiter{')'};
  return in;
}

// Определение оператора << для DataStruct
std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
  std::ostream::sentry guard(out);
  if (!guard) {
    return out;
  }
  StreamGuard s_guard(out);
  out << std::fixed;
  out << "(:key1 " << std::setprecision(1) <<  data.key1 << "d:key2 "
      << data.key2 << "ll:key3 \"" << data.key3 << "\":)";
  return out;
}

} // namespace lazareva

