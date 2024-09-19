#include "datastruct.h"
#include <iostream>

namespace skopchenko {

  std::istream& operator>>(std::istream& is, DataStruct& data) {
    is >> data.key1 >> data.key2.first >> data.key2.second >> data.key3;
    return is;
  }

  std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << data.key1 << " " << data.key2.first << " " << data.key2.second << " " << data.key3;
    return os;
  }

}
