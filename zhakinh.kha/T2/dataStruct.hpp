#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <utility>

namespace zhakha {
    struct DataStruct {
        double key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };

    bool operator<(const DataStruct& lhs, const DataStruct& rhs);
    std::istream& operator>>(std::istream& in, DataStruct& data);
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
}

#endif // DATASTRUCT_HPP
