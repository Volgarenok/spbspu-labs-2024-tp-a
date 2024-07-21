#include "dataStruct.hpp"
#include "delimiter.hpp"
#include <iomanip>
#include <iostream>

namespace lazareva {

  using namespace std; // Добавлен using namespace std

  istream& operator>>(istream& in, double& value) {
    istream::sentry guard(in);
    if (!guard) {
      return in;
    }
    in >> value;
    return in;
  }

  istream& operator>>(istream& in, long long& value) {
    istream::sentry guard(in);
    if (!guard) {
      return in;
    }
    in >> value;
    return in;
  }

  istream& operator>>(istream& in, string& value) {
    istream::sentry guard(in);
    if (!guard) {
      return in;
    }
    getline(in, value, '"');
    return in;
  }

  istream& operator>>(istream& in, DataStruct& data) {
    istream::sentry guard(in);
    if (!guard) {
      return in;
    }
    in.ignore(1); // Пропускаем символ '('
    in >> data.key1 >> data.key2;
    getline(in, data.key3, '"');
    in.ignore(1); // Пропускаем символ ')'
    return in;
  }

  ostream& operator<<(ostream& out, const DataStruct& data) {
    ostream::sentry guard(out);
    if (!guard) {
      return out;
    }
    out << std::fixed;
    out << "(:key1 " << std::setprecision(1) << data.key1 << "d:key2 "
        << data.key2 << "ll:key3 \"" << data.key3 << "\":)";
    return out;
  }
}

