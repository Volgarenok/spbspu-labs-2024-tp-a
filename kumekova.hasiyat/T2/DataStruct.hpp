#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>

namespace kumekova {
class DataStruct {
public:
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;

    friend std::istream& operator>>(std::istream& stream, DataStruct& dataStruct);
    friend std::ostream& operator<<(std::ostream& stream, const DataStruct& dataStruct);
    bool operator<(const DataStruct& rhs) const;
};

}

#endif
