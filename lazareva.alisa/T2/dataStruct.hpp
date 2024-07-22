#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>
#include <string>

namespace lazareva {
  struct DataStruct {
    double key1;
    long long key2;
    std::string key3;

    // Перегрузка оператора << для вывода в поток вывода
    friend std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
      out << data.key1 << " " << data.key2 << " " << data.key3;
      return out;
    }

    // Перегрузка оператора >> для считывания из потока ввода
    friend std::istream& operator>>(std::istream& in, DataStruct& data) {
      in >> data.key1 >> data.key2 >> data.key3;
      return in;
    }
  };

  // Перегрузка оператора < для сравнения объектов DataStruct
  bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 < rhs.key1) {
      return true;
    } else if (lhs.key1 == rhs.key1 && lhs.key2 < rhs.key2) {
      return true;
    } else if (lhs.key1 == rhs.key1 && lhs.key2 == rhs.key2 && lhs.key3 < rhs.key3) {
      return true;
    }
    return false;
  }
}

#endif
