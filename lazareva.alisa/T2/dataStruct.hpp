#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <iostream>
#include <string>

namespace lazareva {
  struct DataStruct {
    double key1;
    long long key2;
    std::string key3;

    // Объявления операторов как "друзей" структуры
    friend std::istream& operator>>(std::istream& in, DataStruct& data);
    friend std::ostream& operator<<(std::ostream& out, const DataStruct& data);
    friend bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  };

  // Определения операторов вне класса, но внутри пространства имен
  std::istream& operator>>(std::istream& in, DataStruct& data) {
    in >> data.key1 >> data.key2 >> data.key3;
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    out << data.key1 << " " << data.key2 << " " << data.key3;
    return out;
  }

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
